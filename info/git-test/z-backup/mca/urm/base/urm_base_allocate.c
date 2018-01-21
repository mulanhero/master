/*
 * Copyright (c) 2004-2005 The Trustees of Indiana University and Indiana
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
 * $COPYRIGHT$
 * 
 * Additional copyrights may follow
 * 
 * $HEADER$
 */

#include "orte_config.h"

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "orte/constants.h"
#include "orte/types.h"

#include "opal/mca/mca.h"
#include "opal/mca/base/base.h"
#include "opal/class/opal_list.h"
#include "opal/util/output.h"
#include "opal/dss/dss.h"
#include "opal/util/argv.h"

#include "orte/util/show_help.h"
#include "orte/mca/errmgr/errmgr.h"
#include "orte/mca/rmaps/base/base.h"
#include "orte/util/name_fns.h"
#include "orte/runtime/orte_globals.h"
#include "orte/runtime/orte_wait.h"
#include "orte/util/hostfile/hostfile.h"
#include "orte/util/dash_host/dash_host.h"
#include "orte/util/proc_info.h"
#include "orte/util/comm/comm.h"
#include "orte/mca/state/state.h"
#include "orte/runtime/orte_quit.h"

//#include "orte/mca/ras/base/ras_private.h"
#include "orte/mca/urm/base/base.h"

/*
 * Function for selecting one component from all those that are
 * available.
 */
void orte_urm_base_allocate(int uid, uint32_t *jobid, void **cbdata)
{
	int rc;
	uint32_t tmp_jobid;
	char *tmp_resp;

    if (NULL != orte_urm_base.active_module)  {
    	rc = orte_urm_base.active_module->allocate(&tmp_jobid, &tmp_resp);
    	printf("jimmy-in-base-allocate: tmp_jobid = %d\n", tmp_jobid);
    	printf("jimmy-in-base-allocate: tmp_resp = %s\n", tmp_resp);
    	*jobid = tmp_jobid;
    	*cbdata = (void *)tmp_resp;
    	printf("jimmy-in-base-allocate: cbdata = %s\n", (char*)*cbdata);
    }
}
