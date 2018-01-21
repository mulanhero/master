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

#include "ipc/hamster_ipc.h"

bool heartbeat_started = false;

//each nodelist is to hold hosts for a comm_spawn job
opal_list_t nodelist[UCHAR_MAX];

int slot_required[UCHAR_MAX];

bool allocate_finish_flag[UCHAR_MAX];

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
  char *mpijobname;
  int32_t nslots;
};

struct  _MpiJobAllocationUpdateProto
{
  ProtobufCMessage base;
  size_t n_newlyallocatedresources;
  AllocatedResourceProto **newlyallocatedresources;
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
	int i, j;
	int allocated_slots;

	if (!heartbeat_started) {
		heartbeat_started = true;
	}

	HeartbeatRequestProto request = HEARTBEAT_REQUEST_PROTO__INIT;
	HeartbeatResponseProto *response = NULL;

	if (0 != mpirun_am_get_allocation_result(&request, &response)) {
		opal_output(0, "%s:orte_ras_heartbeat_am: mpirun_am_heartbeat failed", ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
		goto cleanup_next_heartbeat;
	}

	if (response->n_updates == 0) {
		goto cleanup_next_heartbeat;
	} else {
		for (i = 0; i < response->n_updates; i++) {
			for (j = 0; j < response->updates[i]->n_newlyallocatedresources; j++) {
				char *hostname = response->updates[i]->newlyallocatedresources[j]->hostname;
				int nslots = response->updates[i]->newlyallocatedresources[j]->nslots;
				char *mpijobname = response->updates[i]->newlyallocatedresources[j]->mpijobname;

				char **tmp = opal_argv_split(mpijobname, "_");
				int local_jobid = atoi(tmp[1]);

				orte_node_t *node = OBJ_NEW(orte_node_t);
				node->name = strdup(hostname);
				node->state = ORTE_NODE_STATE_UP;
				node->slots_inuse = 0;
				node->slots_max = 0;
				node->slots = nslots;
				opal_list_append(&nodelist[local_jobid], &node->super);

				/*
				 * here, we check if all slots required for a local_jobid are
				 * allocated, if so, we set the allocate_finish_flag to be true.
				 */
				int total_allocated = get_allocated_slot_num(&nodelist[local_jobid]);
				if (total_allocated == slot_required[local_jobid]) {
					allocate_finish_flag[local_jobid] = true;
				}
			}
		}
	}

cleanup_next_heartbeat:
	if (!response) {
		heartbeat_response_proto__free_unpacked(response, NULL);
	}

	/* the next hearbeat */
	opal_event_t *ev = xmalloc(sizeof(opal_event_t));
	struct timeval delay;
	delay.tv_sec = 1;
	delay.tv_usec = 0;

	opal_event_evtimer_set(orte_event_base, ev, orte_ras_heartbeat_cb, NULL);
	opal_event_evtimer_add(ev, &delay);
}

static int orte_ras_yarn_allocate_once(int local_jobid, int np) {
	char *mpijobname;
	orte_job_t *daemons;

	AllocateRequestProto request = ALLOCATE_REQUEST_PROTO__INIT;
	AllocateResponseProto *responseProto = NULL;
	request.np = np;

//	daemons = orte_get_job_data_object(ORTE_PROC_MY_NAME->jobid);
	if (0 > asprintf(&mpijobname, "%d_%d", ORTE_PROC_MY_NAME->jobid, local_jobid)) {
		opal_outout(0, "%s orte_ras_yarn_allocate_once: asprintf failed", ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
		goto cleanup;
	}
	request.mpijobname = mpijobname;


	if (0 != mpirun_am_allocate(&request, &responseProto)) {
		opal_output(0, "%s orte_ras_yarn_allocate_once: mpirun_am_allocate failed", ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
		goto cleanup;
	}

	if (!mpijobname) {
		free(mpijobname);
	}

	if (!responseProto) {
		allocate_response_proto__free_unpacked(responseProto, NULL);
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

static int orte_ras_yarn_allocate(orte_job_t *jdata, opal_list_t* nodes) {
    int i, j, rc;

	uint32_t local_jobid = ORTE_LOCAL_JOBID(jdata->jobid);

	// set managed allocation
    orte_managed_allocation = true;

	//init the nodelist[local_jobid], and allocate_status[local_jobid] for the current job
	OBJ_CONSTRUCT(&nodelist[local_jobid], opal_list_t);
	allocate_finish_flag[local_jobid] = false;

    // calculate all slots needed
    int np = 0;
    orte_app_context_t* app = NULL;
	for (j = 0; j < jdata->apps->size; j++) {
		if (NULL == (app = (orte_app_context_t*) opal_pointer_array_get_item(jdata->apps, j))) {
			continue;
		}
		np += app->num_procs;
	}

	/* just keep the np required for this local_jobid */
	slot_required[local_jobid] = np;

    if (ORTE_SUCCESS != orte_ras_yarn_allocate_once(local_jobid, np)) {
    	opal_output(0, "%s : orte_ras_yarn_allocate : orte_ras_yarn_allocate_once failed", ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
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

	while (!allocate_finish_flag[local_jobid]) {
		usleep(100);
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
