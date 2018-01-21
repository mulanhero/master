/*
 * Copyright (c) 2004-2008 The Trustees of Indiana University and Indiana
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
 *
 * The Unified Resource Management (URM)
 */

#ifndef ORTE_MCA_URM_H
#define ORTE_MCA_URM_H

#include "orte_config.h"
#include "orte/constants.h"
#include "orte/types.h"

#include "opal/mca/mca.h"
#include "opal/mca/event/event.h"
#include "opal/class/opal_list.h"

#include "orte/runtime/orte_globals.h"

#include "urm_types.h"

BEGIN_C_DECLS

typedef int (*orte_urm_base_module_allocate_fn_t)(uint32_t *jobid, char** response);
typedef int (*orte_urm_base_module_finalize_fn_t)(void);


struct orte_urm_base_module_2_0_0_t {
    orte_urm_base_module_allocate_fn_t              allocate;
    orte_urm_base_module_finalize_fn_t              finalize;
};
typedef struct orte_urm_base_module_2_0_0_t orte_urm_base_module_2_0_0_t;
typedef orte_urm_base_module_2_0_0_t orte_urm_base_module_t;

//=============================================================

/**
 * Component init / selection
 * urm component
 */
struct orte_urm_base_component_2_0_0_t {
    /** Base MCA structure */
    mca_base_component_t base_version;
    /** Base MCA data */
    mca_base_component_data_t base_data;
};
typedef struct orte_urm_base_component_2_0_0_t orte_urm_base_component_2_0_0_t;
typedef orte_urm_base_component_2_0_0_t orte_urm_base_component_t;


/**
 * Macro for use in components that are of type urm
 */
#define ORTE_URM_BASE_VERSION_2_0_0 \
  MCA_BASE_VERSION_2_0_0, \
  "urm", 2, 0, 0


END_C_DECLS

#endif
