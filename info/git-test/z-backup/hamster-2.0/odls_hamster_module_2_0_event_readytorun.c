/*
 * Copyright (c) 2004-2007 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2004-2008 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2004-2005 High Performance Computing Center Stuttgart,
 *                         University of Stuttgart.  All rights reserved.
 * Copyright (c) 2004-2005 The Regents of the University of California.
 *                         All rights reserved.
 * Copyright (c) 2007-2010 Oracle and/or its affiliates.  All rights reserved.
 * Copyright (c) 2007      Evergrid, Inc. All rights reserved.
 * Copyright (c) 2008-2012 Cisco Systems, Inc.  All rights reserved.
 * Copyright (c) 2010      IBM Corporation.  All rights reserved.
 * Copyright (c) 2011-2012 Los Alamos National Security, LLC.  All rights
 *                         reserved.
 *
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

/*
 * There is a complicated sequence of events that occurs when the
 * parent forks a child process that is intended to launch the target
 * executable.
 *
 * Before the child process exec's the target executable, it might tri
 * to set the affinity of that new child process according to a
 * complex series of rules.  This binding may fail in a myriad of
 * different ways.  A lot of this code deals with reporting that error
 * occurately to the end user.  This is a complex task in itself
 * because the child process is not "really" an ORTE process -- all
 * error reporting must be proxied up to the parent who can use normal
 * ORTE error reporting mechanisms.
 *
 * Here's a high-level description of what is occurring in this file:
 *
 * - parent opens a pipe
 * - parent forks a child
 * - parent blocks reading on the pipe: the pipe will either close
 *   (indicating that the child successfully exec'ed) or the child will
 *   write some proxied error data up the pipe
 *
 * - the child tries to set affinity and do other housekeeping in
 *   preparation of exec'ing the target executable
 * - if the child fails anywhere along the way, it sends a message up
 *   the pipe to the parent indicating what happened -- including a
 *   rendered error message detailing the problem (i.e., human-readable).
 * - it is important that the child renders the error message: there
 *   are so many errors that are possible that the child is really the
 *   only entity that has enough information to make an accuate error string
 *   to report back to the user.
 * - the parent reads this message + rendered string in and uses ORTE
 *   reporting mechanisms to display it to the user
 * - if the problem was only a warning, the child continues processing
 *   (potentially eventually exec'ing the target executable).
 * - if the problem was an error, the child exits and the parent
 *   handles the death of the child as appropriate (i.e., this ODLS
 *   simply reports the error -- other things decide what to do).
 */

#include "orte_config.h"
#include "orte/constants.h"
#include "orte/types.h"

#ifdef HAVE_STRING_H
#include <string.h>
#endif
#include <stdlib.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <errno.h>
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_WAIT_H
#include <sys/wait.h>
#endif
#include <signal.h>
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#ifdef HAVE_NETDB_H
#include <netdb.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif  /* HAVE_SYS_STAT_H */
#ifdef HAVE_STDARG_H
#include <stdarg.h>
#endif
#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#include "odls_hamster.h"

#include "opal/mca/hwloc/hwloc.h"
#include "opal/mca/hwloc/base/base.h"
#include "opal/mca/shmem/base/base.h"
#include "opal/class/opal_pointer_array.h"
#include "opal/util/opal_environ.h"
#include "opal/util/show_help.h"
#include "opal/util/fd.h"
#include "opal/util/argv.h"
#include "opal/util/os_path.h"
#include "opal/util/path.h"
#include "opal/util/sys_limits.h"
#include "opal/dss/dss.h"
#include "opal/mca/pstat/pstat.h"

#include "orte/util/show_help.h"
#include "orte/util/context_fns.h"
#include "orte/runtime/orte_wait.h"
#include "orte/runtime/orte_globals.h"
#include "orte/mca/errmgr/errmgr.h"
#include "orte/mca/ess/ess.h"
#include "orte/mca/ess/base/base.h"
#include "orte/mca/state/state.h"
#include "orte/mca/sensor/sensor.h"
#include "orte/mca/iof/base/iof_base_setup.h"
#include "orte/mca/plm/plm.h"
#include "orte/util/name_fns.h"

#include "orte/mca/odls/base/base.h"
#include "orte/mca/odls/base/odls_private.h"


#include "ipc/src/orted_ortedservice_ipc.h"

/*
 * Struct written up the pipe from the child to the parent.
 */
typedef struct {
    /* True if the child has died; false if this is just a warning to
       be printed. */
    bool fatal;
    /* Relevant only if fatal==true */
    int exit_status;

    /* Length of the strings that are written up the pipe after this
       struct */
    int file_str_len;
    int topic_str_len;
    int msg_str_len;
} pipe_err_msg_t;

/*
 * Max length of strings from the pipe_err_msg_t
 */
#define MAX_FILE_LEN 511
#define MAX_TOPIC_LEN MAX_FILE_LEN


bool readytorun = false;

static void check_ready_to_run(int fd, short event, void *data);

/*
 * Module functions (function pointers used in a struct)
 */
static int orte_odls_default_launch_local_procs(opal_buffer_t *data);
static int orte_odls_default_kill_local_procs(opal_pointer_array_t *procs);
static int orte_odls_default_signal_local_procs(const orte_process_name_t *proc, int32_t signal);
static int orte_odls_default_restart_proc(orte_proc_t *child);
static int odls_yarn_setup_fork(orte_app_context_t *context,
                                        int32_t num_local_procs,
                                        orte_vpid_t vpid_range,
                                        orte_std_cntr_t total_slots_alloc,
                                        int num_nodes,
                                        bool oversubscribed, char ***environ_copy);
static void orte_odls_yarn_launch_local(int fd, short sd, void *cbdata);
static int compute_num_procs_alive(orte_jobid_t job);
static void timer_cb(int fd, short event, void *cbdata);
static int setup_path(orte_app_context_t *app);
static int setup_child(orte_proc_t *child, orte_job_t *jobdat, char ***env);

/*
 * Explicitly declared functions so that we can get the noreturn
 * attribute registered with the compiler.
 */
static void send_error_show_help(int fd, int exit_status,
                                 const char *file, const char *topic, ...)
    __opal_attribute_noreturn__;
static int do_child(orte_app_context_t* context,
                    orte_proc_t *child,
                    char **environ_copy,
                    orte_job_t *jobdat, int write_fd,
                    orte_iof_base_io_conf_t opts)
    __opal_attribute_noreturn__;


/*
 * Module
 */
orte_odls_base_module_t orte_odls_yarn_module = {
    orte_odls_base_default_get_add_procs_data,
    orte_odls_default_launch_local_procs,
    orte_odls_default_kill_local_procs,
    orte_odls_default_signal_local_procs,
    orte_odls_base_default_deliver_message,
    orte_odls_base_default_require_sync,
    orte_odls_default_restart_proc
};

static int setup_child(orte_proc_t *child, orte_job_t *jobdat, char ***env)
{
    char *param, *value;
    int rc;

    /* setup the jobid */
    if (ORTE_SUCCESS != (rc = orte_util_convert_jobid_to_string(&value, child->name.jobid))) {
        ORTE_ERROR_LOG(rc);
        return rc;
    }
    if (NULL == (param = mca_base_param_env_var ("orte_ess_jobid"))) {
        ORTE_ERROR_LOG(ORTE_ERR_OUT_OF_RESOURCE);
        rc = ORTE_ERR_OUT_OF_RESOURCE;
        return rc;
    }
    opal_setenv(param, value, true, env);
    free(param);
    free(value);

    /* setup the vpid */
    if (ORTE_SUCCESS != (rc = orte_util_convert_vpid_to_string(&value, child->name.vpid))) {
        ORTE_ERROR_LOG(rc);
        return rc;
    }
    if (NULL == (param = mca_base_param_env_var ("orte_ess_vpid"))) {
        ORTE_ERROR_LOG(ORTE_ERR_OUT_OF_RESOURCE);
        rc = ORTE_ERR_OUT_OF_RESOURCE;
        return rc;
    }
    opal_setenv(param, value, true, env);
    free(param);

    /* although the vpid IS the process' rank within the job, users
     * would appreciate being given a public environmental variable
     * that also represents this value - something MPI specific - so
     * do that here.
     *
     * AND YES - THIS BREAKS THE ABSTRACTION BARRIER TO SOME EXTENT.
     * We know - just live with it
     */
    opal_setenv("OMPI_COMM_WORLD_RANK", value, true, env);
    free(value);  /* done with this now */

    /* users would appreciate being given a public environmental variable
     * that also represents the local rank value - something MPI specific - so
     * do that here.
     *
     * AND YES - THIS BREAKS THE ABSTRACTION BARRIER TO SOME EXTENT.
     * We know - just live with it
     */
    if (ORTE_LOCAL_RANK_INVALID == child->local_rank) {
        ORTE_ERROR_LOG(ORTE_ERR_VALUE_OUT_OF_BOUNDS);
        rc = ORTE_ERR_VALUE_OUT_OF_BOUNDS;
        return rc;
    }
    asprintf(&value, "%lu", (unsigned long) child->local_rank);
    opal_setenv("OMPI_COMM_WORLD_LOCAL_RANK", value, true, env);
    free(value);

    /* users would appreciate being given a public environmental variable
     * that also represents the node rank value - something MPI specific - so
     * do that here.
     *
     * AND YES - THIS BREAKS THE ABSTRACTION BARRIER TO SOME EXTENT.
     * We know - just live with it
     */
    if (ORTE_NODE_RANK_INVALID ==child->node_rank) {
        ORTE_ERROR_LOG(ORTE_ERR_VALUE_OUT_OF_BOUNDS);
        rc = ORTE_ERR_VALUE_OUT_OF_BOUNDS;
        return rc;
    }
    asprintf(&value, "%lu", (unsigned long) child->node_rank);
    opal_setenv("OMPI_COMM_WORLD_NODE_RANK", value, true, env);
    /* set an mca param for it too */
    if(NULL == (param = mca_base_param_env_var ("orte_ess_node_rank"))) {
        ORTE_ERROR_LOG(ORTE_ERR_OUT_OF_RESOURCE);
        rc = ORTE_ERR_OUT_OF_RESOURCE;
        return rc;
    }
    opal_setenv(param, value, true, env);
    free(param);
    free(value);

    /* pass the number of restarts for this proc - will be zero for
     * an initial start, but procs would like to know if they are being
     * restarted so they can take appropriate action
     */
    if (NULL == (param = mca_base_param_env_var ("orte_num_restarts"))) {
        ORTE_ERROR_LOG(ORTE_ERR_OUT_OF_RESOURCE);
        rc = ORTE_ERR_OUT_OF_RESOURCE;
        return rc;
    }
    asprintf(&value, "%d", child->restarts);
    opal_setenv(param, value, true, env);
    free(param);
    free(value);

    /* if the proc should not barrier in orte_init, tell it */
    if (child->do_not_barrier || 0 < child->restarts) {
        if (NULL == (param = mca_base_param_env_var ("orte_do_not_barrier"))) {
            ORTE_ERROR_LOG(ORTE_ERR_OUT_OF_RESOURCE);
            rc = ORTE_ERR_OUT_OF_RESOURCE;
            return rc;
        }
        opal_setenv(param, "1", true, env);
        free(param);
    }

    /* if the proc isn't going to forward IO, then we need to flag that
     * it has "completed" iof termination as otherwise it will never fire
     */
    if (!(ORTE_JOB_CONTROL_FORWARD_OUTPUT & jobdat->controls)) {
        child->iof_complete = true;
    }

    return ORTE_SUCCESS;
}

static int setup_path(orte_app_context_t *app)
{
    int rc;
    char dir[MAXPATHLEN];
    char **argvptr;
    char *pathenv = NULL, *mpiexec_pathenv = NULL;
    char *full_search;

    /* Try to change to the app's cwd and check that the app
       exists and is executable The function will
       take care of outputting a pretty error message, if required
    */
    if (ORTE_SUCCESS != (rc = orte_util_check_context_cwd(app, true))) {
        /* do not ERROR_LOG - it will be reported elsewhere */
        goto CLEANUP;
    }

    /* The prior function will have done a chdir() to jump us to
     * wherever the app is to be executed. This could be either where
     * the user specified (via -wdir), or to the user's home directory
     * on this node if nothing was provided. It seems that chdir doesn't
     * adjust the $PWD enviro variable when it changes the directory. This
     * can cause a user to get a different response when doing getcwd vs
     * looking at the enviro variable. To keep this consistent, we explicitly
     * ensure that the PWD enviro variable matches the CWD we moved to.
     *
     * NOTE: if a user's program does a chdir(), then $PWD will once
     * again not match getcwd! This is beyond our control - we are only
     * ensuring they start out matching.
     */
    getcwd(dir, sizeof(dir));
    opal_setenv("PWD", dir, true, &app->env);
    /* update the initial wdir value too */
    opal_setenv("OMPI_MCA_initial_wdir", dir, true, &app->env);

    /* Search for the OMPI_exec_path and PATH settings in the environment. */
    for (argvptr = app->env; *argvptr != NULL; argvptr++) {
        if (0 == strncmp("OMPI_exec_path=", *argvptr, 15)) {
            mpiexec_pathenv = *argvptr + 15;
        }
        if (0 == strncmp("PATH=", *argvptr, 5)) {
            pathenv = *argvptr + 5;
        }
    }

    /* If OMPI_exec_path is set (meaning --path was used), then create a
       temporary environment to be used in the search for the executable.
       The PATH setting in this temporary environment is a combination of
       the OMPI_exec_path and PATH values.  If OMPI_exec_path is not set,
       then just use existing environment with PATH in it.  */
    if (NULL != mpiexec_pathenv) {
        argvptr = NULL;
        if (pathenv != NULL) {
            asprintf(&full_search, "%s:%s", mpiexec_pathenv, pathenv);
        } else {
            asprintf(&full_search, "%s", mpiexec_pathenv);
        }
        opal_setenv("PATH", full_search, true, &argvptr);
        free(full_search);
    } else {
        argvptr = app->env;
    }

    rc = orte_util_check_context_app(app, argvptr);
    /* do not ERROR_LOG - it will be reported elsewhere */
    if (NULL != mpiexec_pathenv) {
        opal_argv_free(argvptr);
    }

 CLEANUP:
    return rc;
}

/* define a timer release point so that we can wait for
 * file descriptors to come available, if necessary
 */
static void timer_cb(int fd, short event, void *cbdata)
{
    orte_timer_t *tm = (orte_timer_t*)cbdata;
    orte_odls_launch_local_t *ll = (orte_odls_launch_local_t*)tm->payload;

    /* increment the number of retries */
    ll->retries++;

    /* re-attempt the launch */
    opal_event_active(ll->ev, OPAL_EV_WRITE, 1);

    /* release the timer event */
    OBJ_RELEASE(tm);
}

static int compute_num_procs_alive(orte_jobid_t job)
{
    int i;
    orte_proc_t *child;
    int num_procs_alive = 0;

    for (i=0; i < orte_local_children->size; i++) {
        if (NULL == (child = (orte_proc_t*)opal_pointer_array_get_item(orte_local_children, i))) {
            continue;
        }
        if (!child->alive) {
            continue;
        }
        /* do not include members of the specified job as they
         * will be added later, if required
         */
        if (job == child->name.jobid) {
            continue;
        }
        num_procs_alive++;
    }
    return num_procs_alive;
}

static void orte_odls_yarn_launch_local(int fd, short sd, void *cbdata)
{
    orte_app_context_t *app;
    orte_proc_t *child=NULL;
    bool oversubscribed;
    int rc=ORTE_SUCCESS;
    opal_buffer_t *alert;
    orte_std_cntr_t proc_rank;
    char basedir[MAXPATHLEN];
    char **argvsav=NULL;
    int inm, j, idx;
    int total_num_local_procs = 0;
    orte_node_t *node;
    orte_odls_launch_local_t *caddy = (orte_odls_launch_local_t*)cbdata;
    orte_job_t *jobdat;
    orte_jobid_t job = caddy->job;
    orte_odls_base_fork_local_proc_fn_t fork_local = caddy->fork_local;
    char *num_app_ctx = NULL;
    char **nps, *npstring;
    char **firstranks, *firstrankstring;

    /* establish our baseline working directory - we will be potentially
     * bouncing around as we execute various apps, but we will always return
     * to this place as our default directory
     */
    getcwd(basedir, sizeof(basedir));

    /* find the jobdat for this job */
    if (NULL == (jobdat = orte_get_job_data_object(job))) {
        ORTE_ERROR_LOG(ORTE_ERR_NOT_FOUND);
        /* not much we can do here - we are just hosed, so
         * report that to the error manager
         */
        ORTE_ACTIVATE_JOB_STATE(NULL, ORTE_JOB_STATE_FAILED_TO_LAUNCH);
        goto ERROR_OUT;
    }

    /* do we have any local procs to launch? */
    if (0 == jobdat->num_local_procs) {
        /* indicate that we are done trying to launch them */
        goto GETOUT;
    }

    /* see if the mapper thinks we are oversubscribed */
    oversubscribed = false;
    if (NULL == (node = (orte_node_t*)opal_pointer_array_get_item(orte_node_pool, 0))) {
        ORTE_ERROR_LOG(ORTE_ERR_NOT_FOUND);
        ORTE_ACTIVATE_JOB_STATE(jobdat, ORTE_JOB_STATE_FAILED_TO_LAUNCH);
        goto ERROR_OUT;
    }
    if (node->oversubscribed) {
        oversubscribed = true;
    }

#if OPAL_ENABLE_FT_CR == 1
    /*
     * Notify the local SnapC component regarding new job
     */
    if( ORTE_SUCCESS != (rc = orte_snapc.setup_job(job) ) ) {
        /* Silent Failure :/ JJH */
        ORTE_ERROR_LOG(rc);
    }
#endif

    /* MPI-3 requires we provide some further info to the procs,
     * so we pass them as envars to avoid introducing further
     * ORTE calls in the MPI layer
     */
    asprintf(&num_app_ctx, "%lu", (unsigned long)jobdat->num_apps);

    /* Now we preload any files that are needed. This is done on a per
     * app context basis, so let's take the opportunity to build
     * some common envars we need to pass for MPI-3 compatibility
     */
    nps = NULL;
    firstranks = NULL;
    for (j=0; j < jobdat->apps->size; j++) {
        if (NULL == (app = (orte_app_context_t*)opal_pointer_array_get_item(jobdat->apps, j))) {
            continue;
        }
        if(app->used_on_node &&
           (app->preload_binary || NULL != app->preload_files)) {
            if( ORTE_SUCCESS != (rc = orte_odls_base_preload_files_app_context(app)) ) {
                ORTE_ERROR_LOG(rc);
                /* JJH: Do not fail here, instead try to execute without the preloaded options*/
            }
        }
        opal_argv_append_nosize(&nps, ORTE_VPID_PRINT(app->num_procs));
        opal_argv_append_nosize(&firstranks, ORTE_VPID_PRINT(app->first_rank));
    }
    npstring = opal_argv_join(nps, ' ');
    firstrankstring = opal_argv_join(firstranks, ' ');
    opal_argv_free(nps);
    opal_argv_free(firstranks);

#if OPAL_ENABLE_FT_CR == 1
    for (j=0; j < jobdat->apps->size; j++) {
        if (NULL == (app = (orte_app_context_t*)opal_pointer_array_get_item(jobdat->apps, j))) {
            continue;
        }
        orte_sstore.fetch_app_deps(app);
    }
    orte_sstore.wait_all_deps();
#endif

    /* setup to report the proc state to the HNP */
    alert = OBJ_NEW(opal_buffer_t);

    /* compute the total number of local procs currently alive and about to be launched */
    total_num_local_procs = compute_num_procs_alive(job) + jobdat->num_local_procs;

    for (j=0; j < jobdat->apps->size; j++) {
        if (NULL == (app = (orte_app_context_t*)opal_pointer_array_get_item(jobdat->apps, j))) {
            continue;
        }

        /* if this app isn't being used on our node, skip it */
        if (!app->used_on_node) {
            continue;
        }

        /* check the system limits - if we are at our max allowed children, then
         * we won't be allowed to do this anyway, so we may as well abort now.
         * According to the documentation, num_procs = 0 is equivalent to
         * no limit, so treat it as unlimited here.
         */
        if (0 < opal_sys_limits.num_procs) {
            OPAL_OUTPUT_VERBOSE((10,  orte_odls_globals.output,
                                 "%s checking limit on num procs %d #children needed %d",
                                 ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                 opal_sys_limits.num_procs, total_num_local_procs));
            if (opal_sys_limits.num_procs < total_num_local_procs) {
                if (2 < caddy->retries) {
                    /* if we have already tried too many times, then just give up */
                    ORTE_ACTIVATE_JOB_STATE(jobdat, ORTE_JOB_STATE_FAILED_TO_LAUNCH);
                    goto ERROR_OUT;
                }
                /* set a timer event so we can retry later - this
                 * gives the system a chance to let other procs
                 * terminate, thus creating room for new ones
                 */
                ORTE_DETECT_TIMEOUT(1000, 1000, -1, timer_cb, caddy);
                return;
            }
        }


        /* setup the environment for this app */
        if (ORTE_SUCCESS != (rc = odls_yarn_setup_fork(app,
                                                               jobdat->num_local_procs,
                                                               jobdat->num_procs,
                                                               jobdat->total_slots_alloc,
                                                               jobdat->map->num_nodes,
                                                               oversubscribed,
                                                               &app->env))) {

            OPAL_OUTPUT_VERBOSE((10, orte_odls_globals.output,
                                 "%s odls:launch:setup_fork failed with error %s",
                                 ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                 ORTE_ERROR_NAME(rc)));

            /* do not ERROR_LOG this failure - it will be reported
             * elsewhere. The launch is going to fail. Since we could have
             * multiple app_contexts, we need to ensure that we flag only
             * the correct one that caused this operation to fail. We then have
             * to flag all the other procs from the app_context as having "not failed"
             * so we can report things out correctly
             */
            /* cycle through children to find those for this jobid */
            for (idx=0; idx < orte_local_children->size; idx++) {
                if (NULL == (child = (orte_proc_t*)opal_pointer_array_get_item(orte_local_children, idx))) {
                    continue;
                }
                if (OPAL_EQUAL == opal_dss.compare(&job, &(child->name.jobid), ORTE_JOBID) &&
                    j == (int)child->app_idx) {
                    child->exit_code = rc;
                    ORTE_ACTIVATE_PROC_STATE(&child->name, ORTE_PROC_STATE_FAILED_TO_LAUNCH);
                }
            }
            goto GETOUT;
        }

        /* setup the working directory for this app - will jump us
         * to that directory
         */
        if (ORTE_SUCCESS != (rc = setup_path(app))) {
            OPAL_OUTPUT_VERBOSE((5, orte_odls_globals.output,
                                 "%s odls:launch:setup_path failed with error %s(%d)",
                                 ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                 ORTE_ERROR_NAME(rc), rc));
            /* do not ERROR_LOG this failure - it will be reported
             * elsewhere. The launch is going to fail. Since we could have
             * multiple app_contexts, we need to ensure that we flag only
             * the correct one that caused this operation to fail. We then have
             * to flag all the other procs from the app_context as having "not failed"
             * so we can report things out correctly
             */
            /* cycle through children to find those for this jobid */
            for (idx=0; idx < orte_local_children->size; idx++) {
                if (NULL == (child = (orte_proc_t*)opal_pointer_array_get_item(orte_local_children, idx))) {
                    continue;
                }
                if (OPAL_EQUAL == opal_dss.compare(&job, &(child->name.jobid), ORTE_JOBID) &&
                    j == (int)child->app_idx) {
                    child->exit_code = rc;
                    ORTE_ACTIVATE_PROC_STATE(&child->name, ORTE_PROC_STATE_FAILED_TO_LAUNCH);
                }
            }
            goto GETOUT;
        }

        /* add the MPI-3 envars */
        opal_setenv("OMPI_NUM_APP_CTX", num_app_ctx, true, &app->env);
        opal_setenv("OMPI_FIRST_RANKS", firstrankstring, true, &app->env);
        opal_setenv("OMPI_APP_CTX_NUM_PROCS", npstring, true, &app->env);

        /* okay, now let's launch all the local procs for this app using the provided fork_local fn */
        for (proc_rank = 0, idx=0; idx < orte_local_children->size; idx++) {
            if (NULL == (child = (orte_proc_t*)opal_pointer_array_get_item(orte_local_children, idx))) {
                continue;
            }

            /* does this child belong to this app? */
            if (j != (int)child->app_idx) {
                continue;
            }

            /* is this child already alive? This can happen if
             * we are asked to launch additional processes.
             * If it has been launched, then do nothing
             */
            if (child->alive) {

                OPAL_OUTPUT_VERBOSE((5, orte_odls_globals.output,
                                     "%s odls:launch child %s has already been launched",
                                     ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                     ORTE_NAME_PRINT(&child->name)));

                continue;
            }

            /* do we have a child from the specified job. Because the
             * job could be given as a WILDCARD value, we must use
             * the dss.compare function to check for equality.
             */
            if (OPAL_EQUAL != opal_dss.compare(&job, &(child->name.jobid), ORTE_JOBID)) {

                OPAL_OUTPUT_VERBOSE((5, orte_odls_globals.output,
                                     "%s odls:launch child %s is not in job %s being launched",
                                     ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                     ORTE_NAME_PRINT(&child->name),
                                     ORTE_JOBID_PRINT(job)));

                continue;
            }

            OPAL_OUTPUT_VERBOSE((5, orte_odls_globals.output,
                                 "%s odls:launch working child %s",
                                 ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                 ORTE_NAME_PRINT(&child->name)));

            /* ensure we clear any prior info regarding state or exit status in
             * case this is a restart
             */
            child->exit_code = 0;
            child->waitpid_recvd = false;
            /* if we are not forwarding output for this job, then
             * flag iof as complete
             */
            if (ORTE_JOB_CONTROL_FORWARD_OUTPUT & jobdat->controls) {
                child->iof_complete = false;
            } else {
                child->iof_complete = true;
            }
            child->pid = 0;
            if (NULL != child->rml_uri) {
                free(child->rml_uri);
                child->rml_uri = NULL;
            }

            /* check to see if we have enough available file descriptors
             * to launch another child - if not, then let's wait a little
             * while to see if some come free. This can happen if we are
             * in a tight loop over comm_spawn
             */
            if (0 < opal_sys_limits.num_files) {
                int limit;
                limit = 4*total_num_local_procs + 6;
                OPAL_OUTPUT_VERBOSE((10,  orte_odls_globals.output,
                                     "%s checking limit on file descriptors %d need %d",
                                     ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                     opal_sys_limits.num_files, limit));
                if (opal_sys_limits.num_files < limit) {
                    if (2 < caddy->retries) {
                        /* tried enough - give up */
                        child->exit_code = ORTE_PROC_STATE_FAILED_TO_LAUNCH;
                        ORTE_ACTIVATE_PROC_STATE(&child->name, ORTE_PROC_STATE_FAILED_TO_LAUNCH);
                        continue;
                    }
                    /* don't have enough - wait a little time */
                    ORTE_DETECT_TIMEOUT(1000, 1000, -1, timer_cb, caddy);
                    return;
                }
            }

            /* did the user request we display output in xterms? */
            if (NULL != orte_xterm) {
                opal_list_item_t *nmitem;
                orte_namelist_t *nm;
                /* see if this rank is one of those requested */
                for (nmitem = opal_list_get_first(&orte_odls_globals.xterm_ranks);
                     nmitem != opal_list_get_end(&orte_odls_globals.xterm_ranks);
                     nmitem = opal_list_get_next(nmitem)) {
                    nm = (orte_namelist_t*)nmitem;
                    if (ORTE_VPID_WILDCARD == nm->name.vpid ||
                        child->name.vpid == nm->name.vpid) {
                        /* we want this one - modify the app's command to include
                         * the orte xterm cmd. Need to be careful, though, that we
                         * don't modify the app for ALL ranks that use it! So we
                         * will create a copy of the argv so we can restore it later
                         */
                        argvsav = opal_argv_copy(app->argv);
                        /* free the argv */
                        opal_argv_free(app->argv);
                        app->argv = NULL;
                        /* now create a new one that starts with the xtermcmd */
                        for (inm=0; inm < opal_argv_count(orte_odls_globals.xtermcmd); inm++) {
                            opal_argv_append_nosize(&app->argv, orte_odls_globals.xtermcmd[inm]);
                        }
                        /* insert the rank into the correct place as a window title */
                        free(app->argv[2]);
                        asprintf(&app->argv[2], "Rank %s", ORTE_VPID_PRINT(child->name.vpid));
                        /* add back the original argv */
                        for (inm=0; inm < opal_argv_count(argvsav); inm++) {
                            opal_argv_append_nosize(&app->argv, argvsav[inm]);
                        }
                        /* the app exe name itself is in the argvsav array, so
                         * we can recover it from there later
                         */
                        free(app->app);
                        app->app = strdup(orte_odls_globals.xtermcmd[0]);
                        break;
                    } else if (jobdat->num_procs <= nm->name.vpid) {  /* check for bozo case */
                        /* can't be done! */
                        orte_show_help("help-orte-odls-base.txt",
                                       "orte-odls-base:xterm-rank-out-of-bounds",
                                       true, nm->name.vpid, jobdat->num_procs);
                        child->exit_code = ORTE_ERR_SILENT;
                        ORTE_ACTIVATE_PROC_STATE(&child->name, ORTE_PROC_STATE_FAILED_TO_LAUNCH);
                        continue;
                    }

                }
            } else if (NULL != orte_fork_agent) {
                /* we were given a fork agent - use it */
                argvsav = opal_argv_copy(app->argv);
                /* free the argv */
                opal_argv_free(app->argv);
                app->argv = NULL;
                /* now create a new one that starts with the fork agent */
                app->argv = opal_argv_copy(orte_fork_agent);
                /* add back the original argv */
                for (inm=0; NULL != argvsav[inm]; inm++) {
                    opal_argv_append_nosize(&app->argv, argvsav[inm]);
                }
                /* the app exe name itself is in the argvsav array, so
                 * we can recover it from there later
                 */
                free(app->app);
                app->app = opal_path_findv(orte_fork_agent[0], X_OK, orte_launch_environ, NULL);
                if (NULL == app->app) {
                    orte_show_help("help-orte-odls-base.txt",
                                   "orte-odls-base:fork-agent-not-found",
                                   true, orte_process_info.nodename, orte_fork_agent[0]);
                    child->exit_code = ORTE_ERR_SILENT;
                    ORTE_ACTIVATE_PROC_STATE(&child->name, ORTE_PROC_STATE_FAILED_TO_LAUNCH);
                    continue;
                }
            }

            /* setup the rest of the environment with the proc-specific items - these
             * will be overwritten for each child
             */
            if (ORTE_SUCCESS != (rc = setup_child(child, jobdat, &app->env))) {
                ORTE_ERROR_LOG(rc);
                child->exit_code = rc;
                ORTE_ACTIVATE_PROC_STATE(&child->name, ORTE_PROC_STATE_FAILED_TO_LAUNCH);
                continue;
            }

#if OPAL_ENABLE_FT_CR == 1
            /*
             * OPAL CRS components need the opportunity to take action before a process
             * is forked.
             * Needs access to:
             *   - Environment
             *   - Rank/ORTE Name
             *   - Binary to exec
             */
            if( NULL != opal_crs.crs_prelaunch ) {
                if( OPAL_SUCCESS != (rc = opal_crs.crs_prelaunch(child->name.vpid,
                                                                 orte_sstore_base_prelaunch_location,
                                                                 &(app->app),
                                                                 &(app->cwd),
                                                                 &(app->argv),
                                                                 &(app->env) ) ) ) {
                    ORTE_ERROR_LOG(rc);
                    child->exit_code = ORTE_PROC_STATE_FAILED_TO_LAUNCH;
                    ORTE_ACTIVATE_PROC_STATE(&child->name, ORTE_PROC_STATE_FAILED_TO_LAUNCH);
                    continue;
                }
            }
#endif
            if (5 < opal_output_get_verbosity(orte_odls_globals.output)) {
                opal_output(orte_odls_globals.output, "%s odls:launch: spawning child %s",
                            ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                            ORTE_NAME_PRINT(&child->name));

                /* dump what is going to be exec'd */
                if (7 < opal_output_get_verbosity(orte_odls_globals.output)) {
                    opal_dss.dump(orte_odls_globals.output, app, ORTE_APP_CONTEXT);
                }
            }

            rc = fork_local(app, child, app->env, jobdat);
            if (ORTE_SUCCESS != rc) {
                /* do NOT ERROR_LOG this error - it generates
                 * a message/node as most errors will be common
                 * across the entire cluster. Instead, we let orterun
                 * output a consolidated error message for us
                 */
                child->exit_code = ORTE_ERR_SILENT; /* error message already output */
                ORTE_ACTIVATE_PROC_STATE(&child->name, ORTE_PROC_STATE_FAILED_TO_START);
                continue;
            } else {
                child->alive = true;
                ORTE_ACTIVATE_PROC_STATE(&child->name, ORTE_PROC_STATE_RUNNING);
            }
            /* move to next processor */
            proc_rank++;
            /* reset the exe name, if necessary */
            if (NULL != argvsav) {
                /* release the current argv array */
                opal_argv_free(app->argv);
                /* restore the original one */
                app->argv = argvsav;
                argvsav = NULL;
                /* the app exe name itself is now in the argv[0] posn */
                free(app->app);
                app->app = strdup(app->argv[0]);
            }
        }  /* complete launching all children for this app */
        /* reset our working directory back to our default location - if we
         * don't do this, then we will be looking for relative paths starting
         * from the last wdir option specified by the user. Thus, we would
         * be requiring that the user keep track on the cmd line of where
         * each app was located relative to the prior app, instead of relative
         * to their current location
         */
        chdir(basedir);
    }

    OPAL_OUTPUT_VERBOSE((5, orte_odls_globals.output,
                         "%s odls:launch setting waitpids",
                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME)));

    /* start the sensors for this job (if any) */
    orte_sensor.start(jobdat->jobid);

    /* setup the waitpids on the children that started */
    for (idx=0; idx < orte_local_children->size; idx++) {
        if (NULL == (child = (orte_proc_t*)opal_pointer_array_get_item(orte_local_children, idx))) {
            continue;
        }
        if (child->name.jobid == jobdat->jobid && child->alive) {
            orte_wait_cb(child->pid, odls_base_default_wait_local_proc, NULL);
        }
    }

 GETOUT:
    /* tell the state machine that all local procs for this job
     * were launched so that it can do whatever it needs to do,
     * like send a state update message for all procs to the HNP
     */
    ORTE_ACTIVATE_JOB_STATE(jobdat, ORTE_JOB_STATE_LOCAL_LAUNCH_COMPLETE);

 ERROR_OUT:
    /* ensure we reset our working directory back to our default location  */
    chdir(basedir);
    /* release the event */
    OBJ_RELEASE(caddy);
}


static int odls_yarn_setup_fork(orte_app_context_t *context,
                                        int32_t num_local_procs,
                                        orte_vpid_t vpid_range,
                                        orte_std_cntr_t total_slots_alloc,
                                        int num_nodes,
                                        bool oversubscribed, char ***environ_copy)
{
    int i;
    char *param, *param2;

    /* setup base environment: copy the current environ and merge
       in the app context environ */
    if (NULL != context->env) {
        *environ_copy = opal_environ_merge(orte_launch_environ, context->env);
    } else {
        *environ_copy = opal_argv_copy(orte_launch_environ);
    }

    /* special case handling for --prefix: this is somewhat icky,
       but at least some users do this.  :-\ It is possible that
       when using --prefix, the user will also "-x PATH" and/or
       "-x LD_LIBRARY_PATH", which would therefore clobber the
       work that was done in the prior pls to ensure that we have
       the prefix at the beginning of the PATH and
       LD_LIBRARY_PATH.  So examine the context->env and see if we
       find PATH or LD_LIBRARY_PATH.  If found, that means the
       prior work was clobbered, and we need to re-prefix those
       variables. */
    for (i = 0; NULL != context->prefix_dir && NULL != context->env && NULL != context->env[i]; ++i) {
        char *newenv;

        /* Reset PATH */
        if (0 == strncmp("PATH=", context->env[i], 5)) {
            asprintf(&newenv, "%s/bin:%s",
                     context->prefix_dir, context->env[i] + 5);
            opal_setenv("PATH", newenv, true, environ_copy);
            free(newenv);
        }

        /* Reset LD_LIBRARY_PATH */
        else if (0 == strncmp("LD_LIBRARY_PATH=", context->env[i], 16)) {
            asprintf(&newenv, "%s/lib:%s",
                     context->prefix_dir, context->env[i] + 16);
            opal_setenv("LD_LIBRARY_PATH", newenv, true, environ_copy);
            free(newenv);
        }
    }

    /* pass my contact info to the local proc so we can talk */
    param = mca_base_param_env_var ("orte_local_daemon_uri");
    opal_setenv(param, orte_process_info.my_daemon_uri, true, environ_copy);
    free(param);

    /* pass the hnp's contact info to the local proc in case it
     * needs it
     */
    if (NULL != orte_process_info.my_hnp_uri) {
        param = mca_base_param_env_var ("orte_hnp_uri");
        opal_setenv(param, orte_process_info.my_hnp_uri, true, environ_copy);
        free(param);
    }

    /* setup yield schedule - do not override any user-supplied directive! */
    if (oversubscribed) {
        param = mca_base_param_env_var ("mpi_yield_when_idle");
        opal_setenv(param, "1", false, environ_copy);
    } else {
        param = mca_base_param_env_var ("mpi_yield_when_idle");
        opal_setenv(param, "0", false, environ_copy);
    }
    free(param);

    /* set the app_context number into the environment */
    param = mca_base_param_env_var ("orte_app_num");
    asprintf(&param2, "%ld", (long)context->idx);
    opal_setenv(param, param2, true, environ_copy);
    free(param);
    free(param2);

    /* although the total_slots_alloc is the universe size, users
     * would appreciate being given a public environmental variable
     * that also represents this value - something MPI specific - so
     * do that here. Also required by the ompi_attributes code!
     *
     * AND YES - THIS BREAKS THE ABSTRACTION BARRIER TO SOME EXTENT.
     * We know - just live with it
     */
    asprintf(&param2, "%ld", (long)total_slots_alloc);
    opal_setenv("OMPI_UNIVERSE_SIZE", param2, true, environ_copy);
    free(param2);

    /* pass the number of nodes involved in this job */
    param = mca_base_param_env_var ("orte_num_nodes");
    asprintf(&param2, "%ld", (long)num_nodes);
    opal_setenv(param, param2, true, environ_copy);
    free(param);
    free(param2);

#if OPAL_HAVE_HWLOC
    {
        /* pass a param telling the child what type and model of cpu we are on,
         * if we know it. If hwloc has the value, use what it knows. Otherwise,
         * see if we were explicitly given it and use that value.
         */
        hwloc_obj_t obj;
        char *htmp;
        if (NULL != opal_hwloc_topology) {
            obj = hwloc_get_root_obj(opal_hwloc_topology);
            if (NULL != (htmp = (char*)hwloc_obj_get_info_by_name(obj, "CPUType")) ||
                NULL != (htmp = orte_local_cpu_type)) {
                param = mca_base_param_env_var ("orte_cpu_type");
                opal_setenv(param, htmp, true, environ_copy);
                free(param);
            }
            if (NULL != (htmp = (char*)hwloc_obj_get_info_by_name(obj, "CPUModel")) ||
                NULL != (htmp = orte_local_cpu_model)) {
                param = mca_base_param_env_var ("orte_cpu_model");
                opal_setenv(param, htmp, true, environ_copy);
                free(param);
            }
        } else {
            if (NULL != orte_local_cpu_type) {
                param = mca_base_param_env_var ("orte_cpu_type");
                opal_setenv(param, orte_local_cpu_type, true, environ_copy);
                free(param);
            }
            if (NULL != orte_local_cpu_model) {
                param = mca_base_param_env_var ("orte_cpu_model");
                opal_setenv(param, orte_local_cpu_model, true, environ_copy);
                free(param);
            }
        }
    }
#endif

    /* get shmem's best component name so we can provide a hint to the shmem
     * framework. the idea here is to have someone figure out what component to
     * select (via the shmem framework) and then have the rest of the
     * components in shmem obey that decision. for more details take a look at
     * the shmem framework in opal.
     */
    if (NULL != (param2 = opal_shmem_base_best_runnable_component_name())) {
        if (NULL != (param =
                     mca_base_param_env_var ("shmem_RUNTIME_QUERY_hint"))) {

            opal_setenv(param, param2, true, environ_copy);
            free(param);
        }
        free(param2);
    }

    /* push data into environment - don't push any single proc
     * info, though. We are setting the environment up on a
     * per-context basis, and will add the individual proc
     * info later. This also sets the mca param to select
     * the "env" component in the SDS framework.
     */
    orte_ess_env_put(vpid_range, num_local_procs, environ_copy);

    /* forcibly set the local tmpdir base to match ours */
    param = mca_base_param_env_var ("orte_tmpdir_base");
    opal_setenv(param, orte_process_info.tmpdir_base, true, environ_copy);
    free(param);

    /* finally, we will set/unset some mca param to select modules */
    opal_unsetenv("OMPI_MCA_plm", environ_copy);
    opal_unsetenv("OMPI_MCA_ras", environ_copy);
    opal_unsetenv("OMPI_MCA_ess", environ_copy);
    opal_unsetenv("OMPI_MCA_state", environ_copy);
    opal_unsetenv("OMPI_MCA_errmgr", environ_copy);


    opal_setenv("OMPI_MCA_state", "app", true, environ_copy);

    return ORTE_SUCCESS;
}


static bool odls_default_child_died(orte_proc_t *child)
{
    time_t end;
    pid_t ret;

    /* Because of rounding in time (which returns whole seconds) we
     * have to add 1 to our wait number: this means that we wait
     * somewhere between (target) and (target)+1 seconds.  Otherwise,
     * the default 1s actually means 'somwhere between 0 and 1s'. */
    end = time(NULL) + orte_odls_globals.timeout_before_sigkill + 1;
    do {
        ret = waitpid(child->pid, &child->exit_code, WNOHANG);
        if (child->pid == ret) {
            OPAL_OUTPUT_VERBOSE((2, orte_odls_globals.output,
                                 "%s odls:default:WAITPID INDICATES PROC %d IS DEAD",
                                 ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), (int)(child->pid)));

            //========start report exitcode
            int orte_local_jobid =  ORTE_LOCAL_JOBID(child->name.jobid);
            proc_exitcode_t proc_exitcode_array[1] = {child->pid, child->exit_code};
            orted_ortedservice_ipc_report_proc_exitcode(orte_local_jobid, proc_exitcode_array, 1);
            //========end report exitcode

            /* It died -- return success */
            return true;
        } else if (0 == ret) {
            /* with NOHANG specified, if a process has already exited
             * while waitpid was registered, then waitpid returns 0
             * as there is no error - this is a race condition problem
             * that occasionally causes us to incorrectly report a proc
             * as refusing to die. Unfortunately, errno may not be reset
             * by waitpid in this case, so we cannot check it.
         *
         * (note the previous fix to this, to return 'process dead'
         * here, fixes the race condition at the cost of reporting
         * all live processes have immediately died!  Better to
         * occasionally report a dead process as still living -
         * which will occasionally trip the timeout for cases that
         * are right on the edge.)
             */

        /* Do nothing, process still alive */
        } else if (-1 == ret && ECHILD == errno) {
            /* The pid no longer exists, so we'll call this "good
               enough for government work" */
            OPAL_OUTPUT_VERBOSE((2, orte_odls_globals.output,
                                 "%s odls:default:WAITPID INDICATES PID %d NO LONGER EXISTS",
                                 ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), (int)(child->pid)));
            return true;
        }

        /* Bogus delay for 1 msec - let's actually give the CPU some time
         * to quit the other process (sched_yield() -- even if we have it
         * -- changed behavior in 2.6.3x Linux flavors to be undesirable)
         * Don't use select on a bogus file descriptor here as it has proven
         * unreliable and sometimes immediately returns - we really, really
         * -do- want to wait a bit!
         */
        usleep(1000);
    } while (time(NULL) < end);

    /* The child didn't die, so return false */
    return false;
}

static int odls_default_kill_local(pid_t pid, int signum)
{
    if (orte_forward_job_control) {
        pid = -pid;
    }
    if (0 != kill(pid, signum)) {
        if (ESRCH != errno) {
            OPAL_OUTPUT_VERBOSE((2, orte_odls_globals.output,
                                 "%s odls:default:SENT KILL %d TO PID %d GOT ERRNO %d",
                                 ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), signum, (int)pid, errno));
            return errno;
        }
    }
    OPAL_OUTPUT_VERBOSE((2, orte_odls_globals.output,
                         "%s odls:default:SENT KILL %d TO PID %d SUCCESS",
                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), signum, (int)pid));
    return 0;
}

int orte_odls_default_kill_local_procs(opal_pointer_array_t *procs)
{
    int rc;

    if (ORTE_SUCCESS != (rc = orte_odls_base_default_kill_local_procs(procs,
                                    odls_default_kill_local, odls_default_child_died))) {
        ORTE_ERROR_LOG(rc);
        return rc;
    }
    return ORTE_SUCCESS;
}


static void set_handler_default(int sig)
{
    struct sigaction act;

    act.sa_handler = SIG_DFL;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);

    sigaction(sig, &act, (struct sigaction *)0);
}

/*
 * Internal function to write a rendered show_help message back up the
 * pipe to the waiting parent.
 */
static int write_help_msg(int fd, pipe_err_msg_t *msg, const char *file,
                          const char *topic, va_list ap)
{
    int ret;
    char *str;

    if (NULL == file || NULL == topic) {
        return OPAL_ERR_BAD_PARAM;
    }

    str = opal_show_help_vstring(file, topic, true, ap);

    msg->file_str_len = (int) strlen(file);
    if (msg->file_str_len > MAX_FILE_LEN) {
        ORTE_ERROR_LOG(ORTE_ERR_BAD_PARAM);
        return ORTE_ERR_BAD_PARAM;
    }
    msg->topic_str_len = (int) strlen(topic);
    if (msg->topic_str_len > MAX_TOPIC_LEN) {
        ORTE_ERROR_LOG(ORTE_ERR_BAD_PARAM);
        return ORTE_ERR_BAD_PARAM;
    }
    msg->msg_str_len = (int) strlen(str);

    /* Only keep writing if each write() succeeds */
    if (OPAL_SUCCESS != (ret = opal_fd_write(fd, sizeof(*msg), msg))) {
        goto out;
    }
    if (msg->file_str_len > 0 &&
        OPAL_SUCCESS != (ret = opal_fd_write(fd, msg->file_str_len, file))) {
        goto out;
    }
    if (msg->topic_str_len > 0 &&
        OPAL_SUCCESS != (ret = opal_fd_write(fd, msg->topic_str_len, topic))) {
        goto out;
    }
    if (msg->msg_str_len > 0 &&
        OPAL_SUCCESS != (ret = opal_fd_write(fd, msg->msg_str_len, str))) {
        goto out;
    }

 out:
    free(str);
    return ret;
}


/* Called from the child to send a warning show_help message up the
   pipe to the waiting parent. */
#if OPAL_HAVE_HWLOC
static int send_warn_show_help(int fd, const char *file,
                               const char *topic, ...)
{
    int ret;
    va_list ap;
    pipe_err_msg_t msg;

    msg.fatal = false;
    msg.exit_status = 0; /* ignored */

    /* Send it */
    va_start(ap, topic);
    ret = write_help_msg(fd, &msg, file, topic, ap);
    va_end(ap);

    return ret;
}
#endif

/* Called from the child to send an error message up the pipe to the
   waiting parent. */
static void send_error_show_help(int fd, int exit_status,
                                 const char *file, const char *topic, ...)
{
    int ret;
    va_list ap;
    pipe_err_msg_t msg;

    msg.fatal = true;
    msg.exit_status = exit_status;

    /* Send it */
    va_start(ap, topic);
    ret = write_help_msg(fd, &msg, file, topic, ap);
    va_end(ap);

    exit(exit_status);
}

static int do_child(orte_app_context_t* context,
                    orte_proc_t *child,
                    char **environ_copy,
                    orte_job_t *jobdat, int write_fd,
                    orte_iof_base_io_conf_t opts)
{
    int i;
    sigset_t sigs;
    long fd, fdmax = sysconf(_SC_OPEN_MAX);
#if OPAL_HAVE_HWLOC
    int rc;
    char *param, *msg;
#endif

    if (orte_forward_job_control) {
        /* Set a new process group for this child, so that a
           SIGSTOP can be sent to it without being sent to the
           orted. */
        setpgid(0, 0);
    }

    /* Setup the pipe to be close-on-exec */
    fcntl(write_fd, F_SETFD, FD_CLOEXEC);

    if (NULL != child) {
        /* setup stdout/stderr so that any error messages that we
           may print out will get displayed back at orterun.

           NOTE: Definitely do this AFTER we check contexts so
           that any error message from those two functions doesn't
           come out to the user. IF we didn't do it in this order,
           THEN a user who gives us a bad executable name or
           working directory would get N error messages, where
           N=num_procs. This would be very annoying for large
           jobs, so instead we set things up so that orterun
           always outputs a nice, single message indicating what
           happened
        */
        if (ORTE_SUCCESS != (i = orte_iof_base_setup_child(&opts,
                                                           &environ_copy))) {
            ORTE_ERROR_LOG(i);
            send_error_show_help(write_fd, 1,
                                 "help-orte-odls-default.txt",
                                 "iof setup failed",
                                 orte_process_info.nodename, context->app);
            /* Does not return */
        }

#if OPAL_HAVE_HWLOC
        {
            hwloc_cpuset_t cpuset;

            /* Set process affinity, if given */
            if (NULL != child->cpu_bitmap) {
                /* convert the list to a cpu bitmap */
                cpuset = hwloc_bitmap_alloc();
                if (0 != (rc = hwloc_bitmap_list_sscanf(cpuset, child->cpu_bitmap))) {
                    /* See comment above about "This may be a small memory leak" */
                    asprintf(&msg, "hwloc_bitmap_sscanf returned \"%s\" for the string \"%s\"",
                             opal_strerror(rc), child->cpu_bitmap);
                    if (NULL == msg) {
                        msg = "failed to convert bitmap list to hwloc bitmap";
                    }
                    if (OPAL_BINDING_REQUIRED(jobdat->map->binding)) {
                        /* If binding is required, send an error up the pipe (which exits
                           -- it doesn't return). */
                        send_error_show_help(write_fd, 1, "help-orte-odls-default.txt",
                                             "binding generic error",
                                             orte_process_info.nodename,
                                             context->app, msg,
                                             __FILE__, __LINE__);
                    } else {
                        send_warn_show_help(write_fd,
                                            "help-orte-odls-default.txt", "not bound",
                                            orte_process_info.nodename, context->app, msg,
                                            __FILE__, __LINE__);
                        goto PROCEED;
                    }
                }
                /* bind as specified */
                rc = hwloc_set_cpubind(opal_hwloc_topology, cpuset, 0);
                if (rc < 0) {
                    char *tmp = NULL;
                    if (errno == ENOSYS) {
                        msg = "hwloc indicates cpu binding not supported";
                    } else if (errno == EXDEV) {
                        msg = "hwloc indicates cpu binding cannot be enforced";
                    } else {
                        asprintf(&msg, "hwloc_set_cpubind returned \"%s\" for bitmap \"%s\"",
                                 opal_strerror(rc), child->cpu_bitmap);
                    }
                    if (OPAL_BINDING_REQUIRED(jobdat->map->binding)) {
                        /* If binding is required, send an error up the pipe (which exits
                           -- it doesn't return). */
                        send_error_show_help(write_fd, 1, "help-orte-odls-default.txt",
                                             "binding generic error",
                                             orte_process_info.nodename, context->app, msg,
                                             __FILE__, __LINE__);
                    } else {
                        send_warn_show_help(write_fd,
                                            "help-orte-odls-default.txt", "not bound",
                                            orte_process_info.nodename, context->app, msg,
                                            __FILE__, __LINE__);
                        if (NULL != tmp) {
                            free(tmp);
                            free(msg);
                        }
                        goto PROCEED;
                    }
                    if (NULL != tmp) {
                        free(tmp);
                        free(msg);
                    }
                }
                if (0 == rc && opal_hwloc_report_bindings) {
                    char tmp1[1024], tmp2[1024];
                    hwloc_cpuset_t mycpus;
                    /* get the cpus we are bound to */
                    mycpus = hwloc_bitmap_alloc();
                    if (hwloc_get_cpubind(opal_hwloc_topology,
                                          mycpus,
                                          HWLOC_CPUBIND_PROCESS) < 0) {
                        opal_output(0, "MCW rank %d is not bound",
                                    child->name.vpid);
                    } else {
                        opal_hwloc_base_cset2str(tmp1, sizeof(tmp1), mycpus);
                        opal_hwloc_base_cset2mapstr(tmp2, sizeof(tmp2), mycpus);
                        opal_output(0, "MCW rank %d bound to %s: %s",
                                    child->name.vpid, tmp1, tmp2);
                    }
                    hwloc_bitmap_free(mycpus);
                    /* avoid reporting it twice */
                    param = mca_base_param_env_var ("hwloc_base_report_bindings");
                    opal_unsetenv(param, &environ_copy);
                    free(param);
                }
                /* set memory affinity policy */
                if (ORTE_SUCCESS != opal_hwloc_base_set_process_membind_policy()) {
                    if (errno == ENOSYS) {
                        msg = "hwloc indicates memory binding not supported";
                    } else if (errno == EXDEV) {
                        msg = "hwloc indicates memory binding cannot be enforced";
                    } else {
                        msg = "failed to bind memory";
                    }
                    if (OPAL_HWLOC_BASE_MBFA_ERROR == opal_hwloc_base_mbfa) {
                        /* If binding is required, send an error up the pipe (which exits
                           -- it doesn't return). */
                        send_error_show_help(write_fd, 1, "help-orte-odls-default.txt",
                                             "memory binding error",
                                             orte_process_info.nodename, context->app, msg,
                                             __FILE__, __LINE__);
                    } else {
                        send_warn_show_help(write_fd,
                                            "help-orte-odls-default.txt", "memory not bound",
                                            orte_process_info.nodename, context->app, msg,
                                            __FILE__, __LINE__);
                        goto PROCEED;
                    }
                }
                /* Set an info MCA param that tells
                   the launched processes that it was bound by us (e.g., so that
                   MPI_INIT doesn't try to bind itself) */
                param = mca_base_param_env_var ("orte_bound_at_launch");
                opal_setenv(param, "1", true, &environ_copy);
                free(param);
                /* ...and provide a nice string representation of what we
                   bound to */
                param = mca_base_param_env_var ("orte_base_applied_binding");
                opal_setenv(param, child->cpu_bitmap, true, &environ_copy);
                free (param);
            }
        }
#endif

    } else if (!(ORTE_JOB_CONTROL_FORWARD_OUTPUT & jobdat->controls)) {
        /* tie stdin/out/err/internal to /dev/null */
        int fdnull;
        for (i=0; i < 3; i++) {
            fdnull = open("/dev/null", O_RDONLY, 0);
            if (fdnull > i && i != write_fd) {
                dup2(fdnull, i);
            }
            close(fdnull);
        }
        fdnull = open("/dev/null", O_RDONLY, 0);
        if (fdnull > opts.p_internal[1]) {
            dup2(fdnull, opts.p_internal[1]);
        }
        close(fdnull);
    }

#if OPAL_HAVE_HWLOC
 PROCEED:
#endif
    /* close all file descriptors w/ exception of stdin/stdout/stderr,
       the pipe used for the IOF INTERNAL messages, and the pipe up to
       the parent. */
    for(fd=3; fd<fdmax; fd++) {
        if (fd != opts.p_internal[1] && fd != write_fd) {
            close(fd);
        }
    }

    if (context->argv == NULL) {
        context->argv = malloc(sizeof(char*)*2);
        context->argv[0] = strdup(context->app);
        context->argv[1] = NULL;
    }

    /* Set signal handlers back to the default.  Do this close to
       the exev() because the event library may (and likely will)
       reset them.  If we don't do this, the event library may
       have left some set that, at least on some OS's, don't get
       reset via fork() or exec().  Hence, the launched process
       could be unkillable (for example). */

    set_handler_default(SIGTERM);
    set_handler_default(SIGINT);
    set_handler_default(SIGHUP);
    set_handler_default(SIGPIPE);
    set_handler_default(SIGCHLD);

    /* Unblock all signals, for many of the same reasons that we
       set the default handlers, above.  This is noticable on
       Linux where the event library blocks SIGTERM, but we don't
       want that blocked by the launched process. */
    sigprocmask(0, 0, &sigs);
    sigprocmask(SIG_UNBLOCK, &sigs, 0);

    /* Exec the new executable */

    if (10 < opal_output_get_verbosity(orte_odls_globals.output)) {
        int jout;
        opal_output(0, "%s STARTING %s", ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), context->app);
        for (jout=0; NULL != context->argv[jout]; jout++) {
            opal_output(0, "%s\tARGV[%d]: %s", ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), jout, context->argv[jout]);
        }
        for (jout=0; NULL != environ_copy[jout]; jout++) {
            opal_output(0, "%s\tENVIRON[%d]: %s", ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), jout, environ_copy[jout]);
        }
    }

    execve(context->app, context->argv, environ_copy);
    send_error_show_help(write_fd, 1,
                         "help-orte-odls-default.txt", "execve error",
                         orte_process_info.nodename, context->app, strerror(errno));
    /* Does not return */
}


static int do_parent(orte_app_context_t* context,
                     orte_proc_t *child,
                     char **environ_copy,
                     orte_job_t *jobdat, int read_fd,
                     orte_iof_base_io_conf_t opts)
{
    int rc;
    pipe_err_msg_t msg;
    char file[MAX_FILE_LEN + 1], topic[MAX_TOPIC_LEN + 1], *str = NULL;

    if (NULL != child && (ORTE_JOB_CONTROL_FORWARD_OUTPUT & jobdat->controls)) {
        /* connect endpoints IOF */
        rc = orte_iof_base_setup_parent(&child->name, &opts);
        if (ORTE_SUCCESS != rc) {
            ORTE_ERROR_LOG(rc);
            close(read_fd);

            if (NULL != child) {
                child->state = ORTE_PROC_STATE_UNDEF;
            }
            return rc;
        }
    }

    /* Block reading a message from the pipe */
    while (1) {
        rc = opal_fd_read(read_fd, sizeof(msg), &msg);

        /* If the pipe closed, then the child successfully launched */
        if (OPAL_ERR_TIMEOUT == rc) {
            break;
        }

        /* If Something Bad happened in the read, error out */
        if (OPAL_SUCCESS != rc) {
            ORTE_ERROR_LOG(rc);
            close(read_fd);

            if (NULL != child) {
                child->state = ORTE_PROC_STATE_UNDEF;
            }
            return rc;
        }

        /* Otherwise, we got a warning or error message from the child */
        if (NULL != child) {
            child->alive = msg.fatal ? 0 : 1;
        }

        /* Read in the strings; ensure to terminate them with \0 */
        if (msg.file_str_len > 0) {
            rc = opal_fd_read(read_fd, msg.file_str_len, file);
            if (OPAL_SUCCESS != rc) {
                orte_show_help("help-orte-odls-default.txt", "syscall fail",
                               true,
                               orte_process_info.nodename, context->app,
                               "opal_fd_read", __FILE__, __LINE__);
                if (NULL != child) {
                    child->state = ORTE_PROC_STATE_UNDEF;
                }
                return rc;
            }
            file[msg.file_str_len] = '\0';
        }
        if (msg.topic_str_len > 0) {
            rc = opal_fd_read(read_fd, msg.topic_str_len, topic);
            if (OPAL_SUCCESS != rc) {
                orte_show_help("help-orte-odls-default.txt", "syscall fail",
                               true,
                               orte_process_info.nodename, context->app,
                               "opal_fd_read", __FILE__, __LINE__);
                if (NULL != child) {
                    child->state = ORTE_PROC_STATE_UNDEF;
                }
                return rc;
            }
            topic[msg.topic_str_len] = '\0';
        }
        if (msg.msg_str_len > 0) {
            str = calloc(1, msg.msg_str_len + 1);
            if (NULL == str) {
                orte_show_help("help-orte-odls-default.txt", "syscall fail",
                               true,
                               orte_process_info.nodename, context->app,
                               "opal_fd_read", __FILE__, __LINE__);
                if (NULL != child) {
                    child->state = ORTE_PROC_STATE_UNDEF;
                }
                return rc;
            }
            rc = opal_fd_read(read_fd, msg.msg_str_len, str);
        }

        /* Print out what we got.  We already have a rendered string,
           so use orte_show_help_norender(). */
        if (msg.msg_str_len > 0) {
            orte_show_help_norender(file, topic, false, str);
            free(str);
            str = NULL;
        }

        /* If msg.fatal is true, then the child exited with an error.
           Otherwise, whatever we just printed was a warning, so loop
           around and see what else is on the pipe (or if the pipe
           closed, indicating that the child launched
           successfully). */
        if (msg.fatal) {
            if (NULL != child) {
                child->state = ORTE_PROC_STATE_FAILED_TO_START;
                child->alive = false;
            }
            close(read_fd);
            return ORTE_ERR_FAILED_TO_START;
        }
    }

    /* If we got here, it means that the pipe closed without
       indication of a fatal error, meaning that the child process
       launched successfully. */
    if (NULL != child) {
        child->state = ORTE_PROC_STATE_RUNNING;
        child->alive = true;
    }
    close(read_fd);

    return ORTE_SUCCESS;
}

static int create_pid_file_for_proc(orte_proc_t* child, int pid) {
    char* dir = getenv("HAMSTER_ORTED_PID_DIR");
    char pid_file_path[1024];
    sprintf(pid_file_path, "%s/%d_%d.hamster_pidfile", dir, child->local_rank, pid);

    // create a blank file
    FILE* f = fopen(pid_file_path, "w");
    if (!f) {
        opal_output(0, "error to open pid file, path=%s", pid_file_path);
        ORTE_ERROR_LOG(ORTE_ERROR);
        return ORTE_ERROR;
    }

    fclose(f);
    return ORTE_SUCCESS;
}

/**
 *  Fork/exec the specified processes
 */
static int odls_default_fork_local_proc(orte_app_context_t* context,
                                        orte_proc_t *child,
                                        char **environ_copy,
                                        orte_job_t *jobdat)
{
    orte_iof_base_io_conf_t opts;
    int rc, p[2];
    pid_t pid;

    if (NULL != child) {
        /* should pull this information from MPIRUN instead of going with
         default */
        opts.usepty = OPAL_ENABLE_PTY_SUPPORT;

        /* do we want to setup stdin? */
        if (NULL != child &&
            (jobdat->stdin_target == ORTE_VPID_WILDCARD ||
             child->name.vpid == jobdat->stdin_target)) {
            opts.connect_stdin = true;
        } else {
            opts.connect_stdin = false;
        }

        if (ORTE_SUCCESS != (rc = orte_iof_base_setup_prefork(&opts))) {
            ORTE_ERROR_LOG(rc);
            if (NULL != child) {
                child->state = ORTE_PROC_STATE_FAILED_TO_START;
                child->exit_code = rc;
            }
            return rc;
        }
    }

    /* A pipe is used to communicate between the parent and child to
       indicate whether the exec ultimately succeeded or failed.  The
       child sets the pipe to be close-on-exec; the child only ever
       writes anything to the pipe if there is an error (e.g.,
       executable not found, exec() fails, etc.).  The parent does a
       blocking read on the pipe; if the pipe closed with no data,
       then the exec() succeeded.  If the parent reads something from
       the pipe, then the child was letting us know why it failed. */
    if (pipe(p) < 0) {
        ORTE_ERROR_LOG(ORTE_ERR_SYS_LIMITS_PIPES);
        if (NULL != child) {
            child->state = ORTE_PROC_STATE_FAILED_TO_START;
            child->exit_code = ORTE_ERR_SYS_LIMITS_PIPES;
        }
        return ORTE_ERR_SYS_LIMITS_PIPES;
    }

    /* Fork off the child */
    pid = fork();
    if (NULL != child) {
        child->pid = pid;
    }

    if ((pid > 0) && (NULL != child)) {
        if (ORTE_SUCCESS != (rc = create_pid_file_for_proc(child, pid))) {
            return ORTE_ERROR;
        }
    }


    //==========report pid start
    if (pid > 0 && (NULL != child)) {
    	int orte_local_jobid =  ORTE_LOCAL_JOBID(jobdat->jobid);
    	int pid_array[1] = { pid };
    	orted_ortedservice_ipc_report_proc_pid(orte_local_jobid, pid_array, 1);
    }
    //=========report pid end

    if (pid < 0) {
        ORTE_ERROR_LOG(ORTE_ERR_SYS_LIMITS_CHILDREN);
        if (NULL != child) {
            child->state = ORTE_PROC_STATE_FAILED_TO_START;
            child->exit_code = ORTE_ERR_SYS_LIMITS_CHILDREN;
        }
        return ORTE_ERR_SYS_LIMITS_CHILDREN;
    }

    if (pid == 0) {
    close(p[0]);
        do_child(context, child, environ_copy, jobdat, p[1], opts);
        /* Does not return */
    }

    close(p[1]);
    return do_parent(context, child, environ_copy, jobdat, p[0], opts);
}


static int check_pid_dir_created() {
    if (!getenv("HAMSTER_ORTED_PID_DIR")) {
        opal_output(0, "failed to get HAMSTER_ORTED_PID_DIR from env");
        ORTE_ERROR_LOG(ORTE_ERR_NOT_FOUND);
        return ORTE_ERROR;
    }
    return ORTE_SUCCESS;
}

static void check_ready_to_run(int fd, short event, void *data)
{
	int *datap = (int *)data;
	int orte_local_jobid = *datap;

	readytorun = orted_ortedservice_ipc_readytorun(orte_local_jobid);

	if(readytorun == false) { //next turn
		opal_event_t *ev = NULL;
		ev = (opal_event_t*) malloc(sizeof(opal_event_t));

		struct timeval delay;
		delay.tv_sec = 1;
		delay.tv_usec = 0;

		opal_event_evtimer_set(orte_event_base, ev, check_ready_to_run, &orte_local_jobid);
		opal_event_evtimer_add(ev, &delay);
	}
}

/**
 * Launch all processes allocated to the current node.
 */
int orte_odls_default_launch_local_procs(opal_buffer_t *data)
{
    int rc;
    orte_jobid_t job;

    /* construct the list of children we are to launch */
    if (ORTE_SUCCESS != (rc = orte_odls_base_default_construct_child_list(data, &job))) {
        OPAL_OUTPUT_VERBOSE((2, orte_odls_globals.output,
                             "%s odls:default:launch:local failed to construct child list on error %s",
                             ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), ORTE_ERROR_NAME(rc)));
        return rc;
    }

    if (ORTE_SUCCESS != (rc = check_pid_dir_created())) {
        return rc;
    }


    //==========================start to check if ready to run
    //TODO: to prevent race condition for the global variable *readytorun*, I will add the lock later
    int orte_local_jobid = ORTE_LOCAL_JOBID(job);
    opal_event_t *ev = NULL;
    ev = (opal_event_t*) malloc(sizeof(opal_event_t));

    struct timeval delay;
    delay.tv_sec = 1;
    delay.tv_usec = 0;

    opal_event_evtimer_set(orte_event_base, ev, check_ready_to_run, &orte_local_jobid);
    opal_event_evtimer_add(ev, &delay);

    while (true) {
    	/**
    	 * if readytorun has become to true, we set it false for
    	 * other orte job, and break the loop immediately
    	 */
    	if(readytorun == true) {
    		readytorun = false;
    		break;
    	}
    }
    //===========================end to check if ready to run


    /* launch the local procs */
    do {
        orte_odls_launch_local_t *ll;
        ll = OBJ_NEW(orte_odls_launch_local_t);
        ll->job = job;
        ll->fork_local = odls_default_fork_local_proc;
        opal_event_set(orte_event_base, ll->ev, -1, OPAL_EV_WRITE,
                       orte_odls_yarn_launch_local, ll);
        opal_event_set_priority(ll->ev, ORTE_SYS_PRI);
        opal_event_active(ll->ev, OPAL_EV_WRITE, 1);
    } while(0);

    return ORTE_SUCCESS;
}


/**
 * Send a signal to a pid.  Note that if we get an error, we set the
 * return value and let the upper layer print out the message.
 */
static int send_signal(pid_t pid, int signal)
{
    int rc = ORTE_SUCCESS;

    OPAL_OUTPUT_VERBOSE((1, orte_odls_globals.output,
                         "%s sending signal %d to pid %ld",
                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                         signal, (long)pid));

    if (orte_forward_job_control) {
    /* Send the signal to the process group rather than the
       process.  The child is the leader of its process group. */
    pid = -pid;
    }
    if (kill(pid, signal) != 0) {
        switch(errno) {
            case EINVAL:
                rc = ORTE_ERR_BAD_PARAM;
                break;
            case ESRCH:
                /* This case can occur when we deliver a signal to a
                   process that is no longer there.  This can happen if
                   we deliver a signal while the job is shutting down.
                   This does not indicate a real problem, so just
                   ignore the error.  */
                break;
            case EPERM:
                rc = ORTE_ERR_PERM;
                break;
            default:
                rc = ORTE_ERROR;
        }
    }

    return rc;
}

static int orte_odls_default_signal_local_procs(const orte_process_name_t *proc, int32_t signal)
{
    int rc;

    if (ORTE_SUCCESS != (rc = orte_odls_base_default_signal_local_procs(proc, signal, send_signal))) {
        ORTE_ERROR_LOG(rc);
        return rc;
    }
    return ORTE_SUCCESS;
}

static int orte_odls_default_restart_proc(orte_proc_t *child)
{
    int rc;

    /* restart the local proc */
    if (ORTE_SUCCESS != (rc = orte_odls_base_default_restart_proc(child, odls_default_fork_local_proc))) {
        OPAL_OUTPUT_VERBOSE((2, orte_odls_globals.output,
                             "%s odls:default:restart_proc failed to launch on error %s",
                             ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), ORTE_ERROR_NAME(rc)));
    }
    return rc;
}

