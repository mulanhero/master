/*
 * Copyright (c) 2004-2007 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2004-2005 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2004-2005 High Performance Computing Center Stuttgart,
 *                         University of Stuttgart.  All rights reserved.
 * Copyright (c) 2004-2005 The Regents of the University of California.
 *                         All rights reserved.
 * Copyright (c) 2011-2012 Los Alamos National Security, LLC.  All rights
 *                         reserved.
 * Copyright (c) 2013 Cisco Systems, Inc.  All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */
#include "orte_config.h"
#include "orte/constants.h"
#include "orte/types.h"

#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "opal/util/argv.h"
#include "opal/util/net.h"
#include "opal/util/if.h"
#include "opal/util/output.h"
#include "opal/opal_socket_errno.h"

#include "orte/util/show_help.h"
#include "orte/mca/errmgr/errmgr.h"
#include "orte/mca/rmaps/base/base.h"
#include "orte/util/name_fns.h"
#include "orte/runtime/orte_globals.h"

#include "orte/mca/ras/base/ras_private.h"
#include "opal/class/opal_bitmap.h"

#include "ras_hamster.h"

#include "ipc/mpirun_am.h"
#include "ipc/generated-sources/hamster-protos.pb-c.h"

bool heartbeat_started = false;

//setup a nodelist array to
opal_list_t nodelist[UCHAR_MAX];

AllocationStatusProto allocate_status[UCHAR_MAX];

char *rid2hostname_global[UINT_MAX];

/*
 * API functions
 */
static int orte_ras_yarn_allocate(orte_job_t *jdata, opal_list_t *nodes);
static int orte_ras_yarn_finalize(void);

/*
 * RAS yarn module
 */
orte_ras_base_module_t orte_ras_yarn_module = {
    orte_ras_yarn_allocate,
    orte_ras_yarn_finalize
};


static int orte_ras_yarn_allocate_once(int np, orte_jobid_t jobid) {

	AllocateRequestProto request = ALLOCATE_REQUEST_PROTO__INIT;
	AllocateResponseProto *responseProto = NULL;
	char *mpijobname = NULL;
	char *policy = "generic";
	uint32_t local_jobid = ORTE_LOCAL_JOBID(jobid);
	/**
	 * jobid_global (extern JobIdProto jobid_global;)
	 * is external global variable initiated at the time
	 * when hamster-run submitting job to AM
	 */
	request.jobid = &jobid_global;
	request.policy = policy;
	request.np = np;
	if (0 > asprintf(&mpijobname, "%ld_%d_%d", jobid_global.timestamp, jobid_global.id, local_jobid)) {
		opal_outout(0, "%s orte_ras_yarn_allocate_once: asprintf failed", ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
		goto cleanup;
	}
	request.mpijobname = mpijobname;

	if (0 != mpirun_am_allocate(&request, &responseProto)) {
		opal_output(0, "%s orte_ras_yarn_allocate_once: mpirun_am_allocate failed", ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
		goto cleanup;
	}

	if (!responseProto) {
		allocate_response_proto__free_unpacked(responseProto, NULL);
	}
	if (!mpijobname) {
		free(mpijobname);
	}
	return ORTE_SUCCESS;

cleanup:
	if (!mpijobname) {
		free(mpijobname);
	}
	if (!responseProto) {
		allocate_response_proto__free_unpacked(responseProto, NULL);
	}
	return ORTE_ERROR;
}

static int get_allocated_slot_num(opal_list_t* nodes)
{
	int total = 0;
	opal_list_item_t *item;
	orte_node_t *node = NULL;

	for (item = opal_list_get_first(nodes);
			item != opal_list_get_end(nodes);
			item = opal_list_get_next(item)) {
		node = (orte_node_t *) item;
		total += node->slots;
	}
	return total;
}
/*
struct  _AllocatedResourceProto
{
  ProtobufCMessage base;
  char *hostname;
  ResourceIdProto *resourceid;
};


struct  _MpiJobAllocationUpdateProto
{
  ProtobufCMessage base;
  char *mpijobname;
  size_t n_newlyallocatedresources;
  AllocatedResourceProto **newlyallocatedresources;
  AllocationStatusProto allocationstatus;
};

struct  _HeartbeatResponseProto
{
  ProtobufCMessage base;
  size_t n_updates;
  MpiJobAllocationUpdateProto **updates;
};
*/
static void orte_ras_heartbeat_cb(int fd, short event, void *data)
{
	if (!heartbeat_started) {
		heartbeat_started = true;
	}

	HeartbeatRequestProto request = HEARTBEAT_REQUEST_PROTO__INIT;
	HeartbeatResponseProto *responseProto = NULL;
	int i, j;
	int allocated_slots;

	/* jobid_global is: extern JobIdProto jobid_global; */
	request.jobid = &jobid_global;
	if (0 != mpirun_am_get_allocation_result(&request, &responseProto)) {
		opal_output(0, "%s:orte_ras_heartbeat_am: mpirun_am_heartbeat failed", ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
		goto cleanup_next_heartbeat;
	}

	if (responseProto->n_updates == 0) {
		goto cleanup_next_heartbeat;
	} else {
		for (i = 0; i < responseProto->n_updates; i++) {
			char *mpijobname = (responseProto->updates)[i]->mpijobname;
			char** tmp = opal_argv_split(mpijobname, '_');
			int local_jobid = atoi(tmp[2]);

			/* record the allocat status */
//			allocate_status[local_jobid] =
//					(responseProto->updates)[i]->allocationstatus;
			//TODO: to be confirmed with Wangda
			allocate_status[local_jobid] = ALLOCATION_STATUS_PROTO__A_ALLOCATION_SUCCEEDED;

			for (j = 0;
					j < (responseProto->updates)[i]->n_newlyallocatedresources;
					j++) {
				bool find_node_flag = false;
				orte_node_t *node = NULL;
				opal_list_item_t *item;

				char *hostname =
						((responseProto->updates)[i]->newlyallocatedresources)[j]->hostname;
				uint32_t rid =
						((responseProto->updates)[i]->newlyallocatedresources)[j]->resourceid->id;
				/* let's record the map (rid, hostname) */
				rid2hostname_global[rid] = xstrdup(hostname);

				for (item = opal_list_get_first(&nodelist[local_jobid]);
						item != opal_list_get_end(&nodelist[local_jobid]);
						item = opal_list_get_next(item)) {
					node = (orte_node_t *) item;
					if (0 == strcmp(node->name, hostname)) {
						find_node_flag = true;
						break;
					}
				}

				if (!find_node_flag) {
					node->slots++;
				} else {
					node = OBJ_NEW(orte_node_t);
					node->name = strdup(hostname);
					node->state = ORTE_NODE_STATE_UP;
					node->slots_inuse = 0;
					node->slots_max = 0;
					node->slots = 1;
					opal_list_append(&nodelist[local_jobid], &node->super);
				}
			}
		}
	}

cleanup_next_heartbeat:
	if (!responseProto) {
		heartbeat_response_proto__free_unpacked(responseProto, NULL);
	}

	/* the next hearbeat */
	opal_event_t *ev = xmalloc(sizeof(opal_event_t));
	struct timeval delay;
	delay.tv_sec = 1;
	delay.tv_usec = 0;

	opal_event_evtimer_set(orte_event_base, ev, orte_ras_heartbeat_cb, NULL);
	opal_event_evtimer_add(ev, &delay);
}


static int orte_ras_yarn_allocate(orte_job_t *jdata, opal_list_t* nodes) {
    int i, j, rc;
    orte_jobid_t jobid;
    time_t timestamp;
    orte_job_t *jdata;

    /* 1) firstly, let's connect to AM, setup the proxy */
	if (0 != mpirun_am_connect_to_am_with_proxy()) {
		opal_output(0, "mpirun_am_connect_to_am_with_proxy failed.");
		mpirun_am_free_connect_proxy();
		return -1;
	}

	/* 2) init the global variable: extern JobIdProto jobid_global; */
	time(&timestamp);
	jobid_global.timestamp = timestamp;
	jdata = opal_pointer_array_get_item(orte_job_data, 0);
	jobid_global.id = jdata->jobid;

    // set managed allocation
    orte_managed_allocation = true;

    //TODO: !!! hardcode, obtain the current jobid from env, need to discuss!!
    char *jobid_str = getenv("CURRENT_JOBID");
    orte_util_convert_string_to_jobid(&jobid, jobid_str);

    jdata = orte_get_job_data_object(jobid);

	uint32_t local_jobid = ORTE_LOCAL_JOBID(jobid);

	//init the nodelist[local_jobid], and allocate_status[local_jobid] for the current job
	OBJ_CONSTRUCT(&nodelist[local_jobid], opal_list_t);
	allocate_status[local_jobid] == ALLOCATION_STATUS_PROTO__A_ALLOCATING;

    // calculate all slots needed
    int slot_num = 0;
    orte_app_context_t* app = NULL;
	for (j = 0; j < jdata->apps->size; j++) {
		if (NULL == (app = (orte_app_context_t*) opal_pointer_array_get_item(jdata->apps, j))) {
			continue;
		}
		slot_num += app->num_procs;
	}

    if (ORTE_SUCCESS != orte_ras_yarn_allocate_once(slot_num, jobid)) {
    	opal_output(0, "%s : orte_ras_yarn_allocate : orte_ras_yarn_allocate_am failed", ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
    	return ORTE_ERROR;
    }

	if (!heartbeat_started) {
		//invoke the timer event to collect the allocated resource from AM
		opal_event_t *ev = xmalloc(sizeof(opal_event_t));

		struct timeval delay;
		delay.tv_sec = 1;
		delay.tv_usec = 0;

		opal_event_evtimer_set(orte_event_base, ev, orte_ras_heartbeat_cb, NULL);
		opal_event_evtimer_add(ev, &delay);
	}

	/* to check the allocation for the current job is finished */
	while (true) {
		if (allocate_status[local_jobid] == ALLOCATION_STATUS_PROTO__A_ALLOCATING) {
			usleep(100);
		} else if (allocate_status[local_jobid] == ALLOCATION_STATUS_PROTO__A_ALLOCATION_FAILED) {
			return ORTE_ERROR;
		} else if (allocate_status[local_jobid] == ALLOCATION_STATUS_PROTO__A_ALLOCATION_SUCCEEDED) {
			int allocated_slots = get_allocated_slot_num(&nodelist[local_jobid]);
			if (allocated_slots == slot_num) {
				break;
			} else {
				return ORTE_ERROR;
			}
		}
	}

	opal_list_item_t *item;
	orte_node_t *node = NULL;
	for (item = opal_list_get_first(&nodelist[local_jobid]);
			item != opal_list_get_end(&nodelist[local_jobid]);
			item = opal_list_get_next(item)) {
		node = (orte_node_t *) item;
		opal_list_append(nodes, &node->super);
	}

    return ORTE_SUCCESS;
}

static int orte_ras_yarn_finalize(void) {
	return ORTE_SUCCESS;
}
