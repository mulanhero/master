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

#include "opal/util/argv.h"
#include "opal/util/net.h"
#include "opal/util/output.h"
#include "opal/opal_socket_errno.h"

#include "orte/util/show_help.h"
#include "orte/mca/errmgr/errmgr.h"
#include "orte/mca/rmaps/base/base.h"
#include "orte/mca/state/state.h"
#include "orte/util/name_fns.h"
#include "orte/runtime/orte_globals.h"

//#include "orte/mca/ras/base/ras_private.h"
#include "urm_slurm.h"

#define SIZE 256

/*
 * Local functions
 */
static int orte_urm_slurm_allocate(uint32_t *jobid, char** response);
static int orte_urm_slurm_finalize(void);

/*
 * RAS slurm module
 */
orte_urm_base_module_t orte_urm_slurm_module = {
    orte_urm_slurm_allocate,
    orte_urm_slurm_finalize
};

static int orte_urm_slurm_allocate(uint32_t *jobid, char** response)
{
	*jobid = 999;
	*response = strdup("your allocate node list = hello world");
	return ORTE_SUCCESS;
}


/*
 * There's really nothing to do here
 */
static int orte_urm_slurm_finalize(void)
{
    
    OPAL_OUTPUT_VERBOSE((1, orte_urm_base.urm_output,
                         "%s urm:slurm:finalize: success (nothing to do)",
                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME)));
    return ORTE_SUCCESS;
}
