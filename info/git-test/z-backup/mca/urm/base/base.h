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
/** @file:
 */

#ifndef ORTE_MCA_URM_BASE_H
#define ORTE_MCA_URM_BASE_H

/*
 * includes
 */
#include "orte_config.h"

#include "orte/mca/urm/urm.h"
/*
 * Global functions for MCA overall collective open and close
 */

BEGIN_C_DECLS

ORTE_DECLSPEC int orte_urm_base_open(void);

#if !ORTE_DISABLE_FULL_SUPPORT
/*
 * globals that might be needed
 */
typedef struct orte_urm_base_t {
    int urm_output;
    opal_list_t urm_opened;
    bool allocation_read;
    orte_urm_base_module_t *active_module;
    int total_slots_alloc;
} orte_urm_base_t;


//todo list
ORTE_DECLSPEC extern orte_urm_base_t orte_urm_base;

/*
 * function definitions
 */
ORTE_DECLSPEC int orte_urm_base_select(void);
ORTE_DECLSPEC int orte_urm_base_close(void);
//
//ORTE_DECLSPEC void orte_ras_base_display_alloc(void);
//
ORTE_DECLSPEC void orte_urm_base_allocate(int uid, uint32_t *jobid, void **cbdata);
ORTE_DECLSPEC int orte_urm_base_finalize(void);
//
//ORTE_DECLSPEC int orte_ras_base_add_hosts(orte_job_t *jdata);

#endif /* ORTE_DISABLE_FULL_SUPPORT */

END_C_DECLS

#endif
