/*
 * Copyright (c) 2004-2007 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2004-2006 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2004-2005 High Performance Computing Center Stuttgart,
 *                         University of Stuttgart.  All rights reserved.
 * Copyright (c) 2004-2005 The Regents of the University of California.
 *                         All rights reserved.
 * Copyright (c) 2006-2007 Cisco Systems, Inc.  All rights reserved.
 * Copyright (c) 2007-2012 Los Alamos National Security, LLC.  All rights
 *                         reserved. 
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 *
 * These symbols are in a file by themselves to provide nice linker
 * semantics.  Since linkers generally pull in symbols by object
 * files, keeping these symbols as the only symbols in this file
 * prevents utility programs such as "ompi_info" from having to import
 * entire components just to query their version and parameters.
 */

#include "orte_config.h"

#ifdef HAVE_STRING_H
#include <string.h>
#endif
#include <sys/types.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <signal.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif

#include "opal/mca/installdirs/installdirs.h"
#include "opal/util/argv.h"
#include "opal/util/output.h"
#include "opal/util/opal_environ.h"
#include "opal/util/path.h"
#include "opal/util/basename.h"
#include "opal/mca/base/mca_base_param.h"

#include "orte/constants.h"
#include "orte/types.h"
#include "orte/util/show_help.h"
#include "orte/util/name_fns.h"
#include "orte/runtime/orte_globals.h"
#include "orte/runtime/orte_wait.h"
#include "orte/runtime/orte_quit.h"
#include "orte/mca/errmgr/errmgr.h"
#include "orte/mca/rmaps/rmaps.h"
#include "orte/mca/state/state.h"

#include "orte/orted/orted.h"

#include "orte/mca/plm/plm.h"
#include "orte/mca/plm/base/plm_private.h"
#include "plm_hamster.h"

#include "orte/mca/rml/rml.h"
#include "orte/mca/grpcomm/grpcomm.h"
#include "orte/mca/ess/base/base.h"
#include "orte/mca/plm/base/base.h"
#include "orte/mca/plm/plm_types.h"

#include "ipc/mpirun_am.h"
#include "ipc/generated-sources/hamster-protos.pb-c.h"

/*
 * Local functions for orte_plm_yarn_module
 */
static int plm_yarn_init(void);
static int plm_yarn_launch_job(orte_job_t *jdata);
static int plm_yarn_orted_terminate_job(orte_jobid_t jobid);
static int plm_yarn_terminate_orteds(void);
static int plm_yarn_signal_job(orte_jobid_t jobid, int32_t signal);
static int plm_yarn_finalize(void);

/*
 * Local utility functions
 */
static int setup_daemon_proc_env_and_argv(orte_proc_t* proc, char ***pargv,
        int *argc, char ***penv);
static int do_launch_daemons(orte_job_t *jdata);
static int finish_job(bool succeed, bool check_proc_status);

/*
 * Local functions for added job state's called in plm_yarn_init
 */
static void launch_daemons(int fd, short args, void* cbdata);
static void plm_yarn_quit(int fd, short args, void* cbdata);
static void plm_yarn_cleanup_job(int fd, short args, void *cbdata);

/*
 * Global variable
 */
orte_plm_base_module_1_0_0_t orte_plm_yarn_module = {
	plm_yarn_init,
    orte_plm_base_set_hnp_name,
    plm_yarn_launch_job,
    NULL,
    plm_yarn_orted_terminate_job,
    plm_yarn_terminate_orteds,
    orte_plm_base_orted_kill_local_procs,
    plm_yarn_signal_job,
    plm_yarn_finalize
};

/**
* Init the module
 */
static int plm_yarn_init(void)
{
    int rc;

    if (ORTE_SUCCESS != (rc = orte_plm_base_comm_start())) {
        ORTE_ERROR_LOG(rc);
        return rc;
    }

        /* point to our launch apps callback */
	if (ORTE_SUCCESS
			!= (rc = orte_state.add_job_state(ORTE_JOB_STATE_LAUNCH_DAEMONS,
					launch_daemons, ORTE_SYS_PRI))) {
		ORTE_ERROR_LOG(rc);
		return rc;
	}

	/* set quit callback */
	if (ORTE_SUCCESS
			!= (rc = orte_state.set_job_state_callback(
					ORTE_JOB_STATE_ALL_JOBS_COMPLETE, plm_yarn_quit))) {
		ORTE_ERROR_LOG(rc);
		opal_output(0,
				"%s plm:yarn:plm_yarn_init: set job state callback with ORTE_JOB_STATE_ALL_JOBS_COMPLETE failed.",
				ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
		exit(rc);
	}

	if (ORTE_SUCCESS
			!= (rc = orte_state.set_job_state_callback(
					ORTE_JOB_STATE_DAEMONS_TERMINATED, plm_yarn_quit))) {
		ORTE_ERROR_LOG(rc);
		opal_output(0,
				"%s plm:yarn:plm_yarn_init: set job state callback with ORTE_JOB_STATE_DAEMONS_TERMINATED failed.",
				ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
		exit(rc);
	}

	if (ORTE_SUCCESS
			!= (rc = orte_state.set_job_state_callback(
					ORTE_JOB_STATE_NOTIFY_COMPLETED, plm_yarn_cleanup_job))) {
		ORTE_ERROR_LOG(rc);
		opal_output(0,
				"%s plm:yarn:init: set job state callback with ORTE_JOB_STATE_NOTIFY_COMPLETED failed",
				ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
		exit(rc);
	}

    return rc;
}

/* When working in this function, ALWAYS jump to "cleanup" if
 * you encounter an error so that orterun will be woken up and
 * the job can cleanly terminate
 */
static int plm_yarn_launch_job(orte_job_t *jdata)
{
    if (ORTE_JOB_CONTROL_RESTART & jdata->controls) {
        /* this is a restart situation - skip to the mapping stage */
        ORTE_ACTIVATE_JOB_STATE(jdata, ORTE_JOB_STATE_MAP);
    } else {
        /* new job - set it up */
        ORTE_ACTIVATE_JOB_STATE(jdata, ORTE_JOB_STATE_INIT);
    }
    return ORTE_SUCCESS;
}


/* setup argv for daemon process */
static int setup_daemon_proc_env_and_argv(orte_proc_t* proc, char ***pargv,
        int *argc, char ***penv)
{
    orte_job_t* daemons;
    int rc;
    char* param;

    /* get daemon job object */
    daemons = orte_get_job_data_object(ORTE_PROC_MY_NAME->jobid);

    *penv = opal_argv_copy(orte_launch_environ);

    /* prepend orted to argv */
    opal_argv_append(argc, pargv, "orted");

    /* ess */
    opal_argv_append(argc, pargv, "-mca");
    opal_argv_append(argc, pargv, "ess");
    opal_argv_append(argc, pargv, "env");

    /* jobid */
    opal_argv_append(argc, pargv, "-mca");
    opal_argv_append(argc, pargv, "orte_ess_jobid");
    if (ORTE_SUCCESS != (rc = orte_util_convert_jobid_to_string(&param, ORTE_PROC_MY_NAME->jobid))) {
        ORTE_ERROR_LOG(rc);
        return rc;
    }
    opal_argv_append(argc, pargv, param);
    free(param);

    /* vpid */
    opal_argv_append(argc, pargv, "-mca");
    opal_argv_append(argc, pargv, "orte_ess_vpid");
    if (ORTE_SUCCESS != (rc = orte_util_convert_vpid_to_string(&param, proc->name.vpid))) {
        ORTE_ERROR_LOG(rc);
        return rc;
    }
    opal_argv_append(argc, pargv, param);
    free(param);

    /* num processes */
    opal_argv_append(argc, pargv, "-mca");
    opal_argv_append(argc, pargv, "orte_ess_num_procs");
    asprintf(&param, "%lu", daemons->num_procs);
    opal_argv_append(argc, pargv, param);
    free(param);

	/* pass the uri of the hnp */
	asprintf(&param, "\"%s\"", orte_rml.get_contact_info());
	opal_argv_append(argc, pargv, "-mca");
	opal_argv_append(argc, pargv, "orte_hnp_uri");
	opal_argv_append(argc, pargv, param);
	free(param);

    /* oob */
    opal_argv_append(argc, pargv, "-mca");
    opal_argv_append(argc, pargv, "oob");
    opal_argv_append(argc, pargv, "tcp");

    /* odls */
    opal_argv_append(argc, pargv, "-mca");
    opal_argv_append(argc, pargv, "odls");
    opal_argv_append(argc, pargv, "yarn");

    /* orted */
	opal_argv_append(argc, pargv, "-mca");
	opal_argv_append(argc, pargv, "state");
	opal_argv_append(argc, pargv, "orted");

    /* print launch commandline and env when this env is specified */
    if (getenv("HAMSTER_VERBOSE")) {
        char* join_argv = opal_argv_join(*pargv, ' ');
        OPAL_OUTPUT_VERBOSE((5, orte_plm_globals.output, "%s plm:yarn launch_daemon argv=%s",
            ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), join_argv));
        if (join_argv) {
            free(join_argv);
        }
    }
    return 0;
}

/*
struct  _LaunchRequestProto
{
  ProtobufCMessage base;
  size_t n_resourcelaunchcontexts;
  ResourceLaunchContextProto **resourcelaunchcontexts;
};

struct  _ResourceLaunchContextProto
{
  ProtobufCMessage base;
  char *mpijobname;
  char *hostname;
  char *commandline;
  size_t n_envs;
  StringStringMapProto **envs;
  protobuf_c_boolean has_localpeers;
  int32_t localpeers;
  protobuf_c_boolean has_containerid;
  int32_t containerid;
};
 */
static int do_launch_daemons(orte_job_t *jdata)
{
	int i, j, rc;
	LaunchResponseProto *responseProto = NULL;
	orte_job_t* daemons;
	char *mpijobname;

	orte_proc_t* proc = NULL;
	char **argv;
	int argc;
	char **env;

	bool error_flag = false;
	bool launch_success_flag = false;

	daemons = orte_get_job_data_object(ORTE_PROC_MY_NAME->jobid);

	/* setup mpijobname */
	uint32_t local_jobid = ORTE_LOCAL_JOBID(jdata->jobid);
	if (0 > asprintf(&mpijobname, "%d_%d", ORTE_PROC_MY_NAME->jobid, local_jobid)) {
		opal_outout(0, "%s orte_ras_yarn_allocate_once: asprintf failed",
				ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
		goto cleanup;
	}

	/* 1. prepare the LaunchRequestProto  */
	LaunchRequestProto request = LAUNCH_REQUEST_PROTO__INIT;
	request.n_resourcelaunchcontexts = daemons->num_procs-1; // HNP is excluded
	request.resourcelaunchcontexts = xmalloc(sizeof(ResourceLaunchContextProto *) * request.n_resourcelaunchcontexts);

	/* when launch_daemon, start from 1 because we don't need launch HNP process */
	for (i = 1; i < jdata->num_procs; i++) {
		argv = NULL;
		argc = 0;
		env = NULL;
		/* setup env/argv  */
		proc = opal_pointer_array_get_item(daemons->procs, i);
		if (!proc) {
			opal_output(0, "%s plm:yarn:do_launch_daemons: proc[%d] is NULL",
			ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), i);
			ORTE_ERROR_LOG(ORTE_ERROR_DEFAULT_EXIT_CODE);
		}

		rc = setup_daemon_proc_env_and_argv(proc, &argv, &argc, &env);
		if (0 != rc) {
			opal_output(0,
					"%s plm:yarn:do_launch_daemons: failed to setup env/argv of proc[%d]",
					ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), i);
			ORTE_ERROR_LOG(ORTE_ERROR_DEFAULT_EXIT_CODE);
			error_flag = true;
			goto cleanup;
		}

		 /* print launch commandline and env when this env is specified */
		if (getenv("HAMSTER_VERBOSE")) {
			char* join_argv = opal_argv_join(argv, ' ');
			OPAL_OUTPUT_VERBOSE((5, orte_plm_globals.output, "%s plm:yarn:do_launch_daemons: launch argv=%s",
							ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), join_argv));
			if (join_argv) {
				free(join_argv);
			}
		}

		OPAL_OUTPUT_VERBOSE((5, orte_plm_globals.output,
						"%s plm:yarn:do_launch_daemons: after setup env and argv for daemon proc=%d.",
						ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), i));

		/* 1. now setup the ResourceLaunchContextProto for each daemon */
		request.resourcelaunchcontexts[i-1] = xmalloc(sizeof(ResourceLaunchContextProto));
		resource_launch_context_proto__init(request.resourcelaunchcontexts[i-1]);

		request.resourcelaunchcontexts[i-1]->mpijobname = xstrdup(mpijobname);
		request.resourcelaunchcontexts[i-1]->hostname = xstrdup(proc->nodename);

		char* join_argv = opal_argv_join(argv, ' ');
		request.resourcelaunchcontexts[i-1]->commandline = xstrdup(join_argv);

		int env_size = opal_argv_len(env);
		request.resourcelaunchcontexts[i-1]->n_envs = env_size;
		request.resourcelaunchcontexts[i-1]->envs = xmalloc(sizeof(StringStringMapProto *) * env_size);
		for (j = 0; j < env_size; j++) {
			char** env_array = opal_argv_split(env[j], '=');
			StringStringMapProto *map = xmalloc(sizeof(StringStringMapProto));
			string_string_map_proto__init(map);
			map->key = xstrdup(env_array[0]);
			map->value = xstrdup(env_array[1]);
			request.resourcelaunchcontexts[i-1]->envs[j] = map;
		}

		request.resourcelaunchcontexts[i-1]->has_localpeers = false;
		request.resourcelaunchcontexts[i-1]->localpeers = -1;
		request.resourcelaunchcontexts[i-1]->has_containerid = false;
		request.resourcelaunchcontexts[i-1]->containerid = -1;

cleanup:
		/* free argv and env for this proc */
		if (argv) {
			opal_argv_free(argv);
		}
		if (env) {
			opal_argv_free(env);
		}
		if (join_argv) {
			free(join_argv);
		}
		if (error_flag) {
			ORTE_UPDATE_EXIT_STATUS(ORTE_ERROR_DEFAULT_EXIT_CODE);
			if (!request.resourcelaunchcontexts) {
				free(request.resourcelaunchcontexts);
			}
			return ORTE_ERROR;
		}
	}

	/* 2. send launch procs request and recv response msg */
	rc = mpirun_am_launch(&request, &responseProto);
	if (0 != rc) {
		opal_output(0,
				"%s plm:yarn:do_launch_daemons: error happened when launch procs with AM",
				ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
		launch_success_flag = false;
	} else {
		launch_success_flag = true;
	}

	/* 3. parse the response, here we do nothing, just free allocated memeory */
	if (!responseProto) {
		launch_response_proto__free_unpacked(responseProto, NULL);
	}

	if (!mpijobname) {
		free(mpijobname);
	}

	for (i = 0; i < request.n_resourcelaunchcontexts; i++) {
		if (!request.resourcelaunchcontexts[i-1]->mpijobname) {
			free(request.resourcelaunchcontexts[i-1]->mpijobname);
		}

		if (!request.resourcelaunchcontexts[i-1]->hostname) {
			free(request.resourcelaunchcontexts[i-1]->hostname);
		}

		if (!request.resourcelaunchcontexts[i-1]->commandline) {
			free(request.resourcelaunchcontexts[i-1]->commandline);
		}

		for (j = 0; j < request.resourcelaunchcontexts[i-1]->n_envs; j++) {
			if (!request.resourcelaunchcontexts[i-1]->envs[j]) {
				free(request.resourcelaunchcontexts[i-1]->envs[j]);
			}
		}

		if (!request.resourcelaunchcontexts[i-1]->envs) {
			free(request.resourcelaunchcontexts[i-1]->envs);
		}

		if (!request.resourcelaunchcontexts[i]) {
			free(request.resourcelaunchcontexts[i]);
		}
	}

	if (!request.resourcelaunchcontexts) {
		free(request.resourcelaunchcontexts);
	}

	//4. return
	if (launch_success_flag) {
		return ORTE_SUCCESS;
	} else {
		ORTE_UPDATE_EXIT_STATUS(ORTE_ERROR_DEFAULT_EXIT_CODE);
		return ORTE_ERROR;
	}
}


static void launch_daemons(int fd, short args, void *cbdata)
{
    orte_state_caddy_t *state = (orte_state_caddy_t*)cbdata;
    orte_job_map_t *map;
    int rc;
    bool failed_launch = true;
    orte_job_t *daemons;
    int launched_proc_num = 0;

    OPAL_OUTPUT_VERBOSE((1, orte_plm_globals.output,
                         "%s plm:yarn:launch_daemons: LAUNCH DAEMONS CALLED",
                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME)));

    /* if we are launching debugger daemons, then just go
     * do it - no new daemons will be launched
     */
    if (ORTE_JOB_CONTROL_DEBUGGER_DAEMON & state->jdata->controls) {
        state->jdata->state = ORTE_JOB_STATE_DAEMONS_LAUNCHED;
        ORTE_ACTIVATE_JOB_STATE(state->jdata, ORTE_JOB_STATE_DAEMONS_REPORTED);
        OBJ_RELEASE(state);
        return;
    }

    /* start by setting up the virtual machine */
    daemons = orte_get_job_data_object(ORTE_PROC_MY_NAME->jobid);
    if (ORTE_SUCCESS != (rc = orte_plm_base_setup_virtual_machine(state->jdata))) {
        ORTE_ERROR_LOG(rc);
        goto cleanup;
    }

   /* if we don't want to launch, then don't attempt to
     * launch the daemons - the user really wants to just
     * look at the proposed process map
     */
    if (orte_do_not_launch) {
        /* set the state to indicate the daemons reported - this
         * will trigger the daemons_reported event and cause the
         * job to move to the following step
         */
        state->jdata->state = ORTE_JOB_STATE_DAEMONS_LAUNCHED;
        ORTE_ACTIVATE_JOB_STATE(state->jdata, ORTE_JOB_STATE_DAEMONS_REPORTED);
        OBJ_RELEASE(state);
        return;
    }

    /* Get the map for this job */
    if (NULL == (map = daemons->map)) {
        ORTE_ERROR_LOG(ORTE_ERR_NOT_FOUND);
        rc = ORTE_ERR_NOT_FOUND;
        goto cleanup;
    }

    if (0 == map->num_new_daemons) {
        /* set the state to indicate the daemons reported - this
         * will trigger the daemons_reported event and cause the
         * job to move to the following step
         */
        OPAL_OUTPUT_VERBOSE((1, orte_plm_globals.output,
                             "%s plm:yarn:launch_daemons: no new daemons to launch",
                             ORTE_NAME_PRINT(ORTE_PROC_MY_NAME)));
        state->jdata->state = ORTE_JOB_STATE_DAEMONS_LAUNCHED;
        if (ORTE_JOB_STATE_DAEMONS_REPORTED == daemons->state) {
            ORTE_ACTIVATE_JOB_STATE(state->jdata, ORTE_JOB_STATE_DAEMONS_REPORTED);
        }
        OBJ_RELEASE(state);
        return;
    }

    rc = do_launch_daemons(state->jdata);
	if (rc != ORTE_SUCCESS) {
		ORTE_ERROR_LOG(rc);
		goto cleanup;
	}

	/* indicate that the daemons for this job were launched */
	state->jdata->state = ORTE_JOB_STATE_DAEMONS_LAUNCHED;
	ORTE_ACTIVATE_JOB_STATE(state->jdata, ORTE_JOB_STATE_DAEMONS_LAUNCHED);
	OPAL_OUTPUT_VERBOSE(
			(5, orte_plm_globals.output, "%s plm:yarn:launch_daemons: launch daemon proc successfully with AM", ORTE_NAME_PRINT(
							ORTE_PROC_MY_NAME)));

    /* flag that launch was successful, so far as we currently know */
    failed_launch = false;

cleanup:
    /* cleanup the caddy */
    OBJ_RELEASE(state);

    /* check for failed launch - if so, force terminate */
    if (failed_launch) {
        ORTE_TERMINATE(ORTE_ERROR_DEFAULT_EXIT_CODE);
    }
}

/*
struct  _FinishJobRequestProto
{
  ProtobufCMessage base;
  FinalJobStatusProto finaljobstatus;
  char *diagnosticmessage;
};

typedef enum _FinalJobStatusProto {
  FINAL_JOB_STATUS_PROTO__JOB_SUCCEEDED = 1,
  FINAL_JOB_STATUS_PROTO__JOB_FAILED = 2,
  FINAL_JOB_STATUS_PROTO__JOB_UNKOWN = 3
} FinalJobStatusProto;
*/
static int finish_job(bool succeed, bool check_proc_status)
{
	int i, j, rc;
	char *diag_msg = "finish_job";
	FinishJobResponseProto *responseProto = NULL;

	/* it's a workaround to disable this checking for a weird error of
	 * job terminated with exit_code = 0, but one of the proc's state
	 * still unterminated, need more tests on this to verify if this
	 * work around impact on other functionality
	 */

	// we need double check if any proc failed
	if (succeed && check_proc_status) {
		// start with 1 because we don't want to check daemon's proc
		for (i = 1; i < orte_job_data->size; i++) {
			orte_job_t* job = opal_pointer_array_get_item(orte_job_data, i);
			if (!job) {
				continue;
			}
			for (j = 0; j < job->procs->size; j++) {
				orte_proc_t* proc = opal_pointer_array_get_item(job->procs, j);
				if (!proc) {
					continue;
				}
				// if any process is non-terminated, we will consider it's error
				if (proc->state < ORTE_PROC_STATE_TERMINATED
						&& proc->state != ORTE_PROC_STATE_WAITPID_FIRED) {
					succeed = false;
					break;
				}
			}
			if (!succeed) {
				break;
			}
		}
	}

	FinishJobRequestProto requestProto = FINISH_JOB_REQUEST_PROTO__INIT;
	requestProto.diagnosticmessage = xstrdup(diag_msg);
	if (succeed) {
		requestProto.finaljobstatus = FINAL_JOB_STATUS_PROTO__JOB_SUCCEEDED;
	} else {
		requestProto.finaljobstatus = FINAL_JOB_STATUS_PROTO__JOB_FAILED;
	}

	if (0 != mpirun_am_finish_job(&requestProto, &responseProto)) {
		opal_output(0,
				"%s plm:hamster: finish_job : error happened when finish job with AM",
				ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
		goto cleanup;
	}

	if (!requestProto.diagnosticmessage) {
		free(requestProto.diagnosticmessage);
	}
	if (!responseProto) {
		finish_job_response_proto__free_unpacked(responseProto, NULL);
	}

	return ORTE_SUCCESS;

cleanup:
	if (!requestProto.diagnosticmessage) {
		free(requestProto.diagnosticmessage);
	}
	if (!responseProto) {
		finish_job_response_proto__free_unpacked(responseProto, NULL);
	}
	return ORTE_ERROR;
}

/**
* Terminate the orteds for a given job
 */
static int plm_yarn_terminate_orteds(void)
{
	finish_job(0 == orte_exit_status, true);
    orte_job_t* jdata = orte_get_job_data_object(ORTE_PROC_MY_NAME->jobid);
    if (ORTE_JOB_STATE_DAEMONS_TERMINATED != jdata->state) {
		/* need to set the #terminated value to avoid an incorrect error msg */
		jdata->num_terminated = jdata->num_procs;
        ORTE_ACTIVATE_JOB_STATE(jdata, ORTE_JOB_STATE_DAEMONS_TERMINATED);
    }
    return ORTE_SUCCESS;
}

/**
 * Signal all the processes in the child srun by sending the signal directly to it
 */
static int plm_yarn_signal_job(orte_jobid_t jobid, int32_t signal)
{
	return ORTE_SUCCESS;
}


static int plm_yarn_finalize(void)
{
    int rc;

    /* cleanup any pending recvs */
    if (ORTE_SUCCESS != (rc = orte_plm_base_comm_stop())) {
        ORTE_ERROR_LOG(rc);
    }

    return ORTE_SUCCESS;
}


static int plm_yarn_orted_terminate_job(orte_jobid_t jobid)
{
	//currently, terminate a specific job is not supported in AM, we just tell AM to finish job and itself
	finish_job(0 == orte_exit_status, true);
	return orte_plm_base_orted_terminate_job(jobid);
}

static void plm_yarn_quit(int fd, short args, void* cbdata)
{
    finish_job(0 == orte_exit_status, true);
    orte_quit(fd, args, cbdata);
}


static void plm_yarn_cleanup_job(int fd, short argc, void *cbdata)
{
    orte_state_caddy_t *caddy = (orte_state_caddy_t*) cbdata;
    orte_job_t *jdata = caddy->jdata;

    OPAL_OUTPUT_VERBOSE((5, orte_plm_globals.output,
                    "%s plm:yarn:cleanup_job: on job %s",
                    ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                    (NULL == jdata) ? "NULL" : ORTE_JOBID_PRINT(jdata->jobid)));

    //currently, terminate a specific job is not supported in AM, we just tell AM to finish the whole job and itself
    finish_job(0 == orte_exit_status, true);

    /* flag that we were notified */
    jdata->state = ORTE_JOB_STATE_NOTIFIED;
    /* send us back thru job complete */
    ORTE_ACTIVATE_JOB_STATE(jdata, ORTE_JOB_STATE_TERMINATED);
    OBJ_RELEASE(caddy);
}
