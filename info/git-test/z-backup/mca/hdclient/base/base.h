/*
 * Copyright (c) 2012      Los Alamos National Security, Inc.  All rights reserved. 
 * $COPYRIGHT$
 * 
 * Additional copyrights may follow
 * 
 * $HEADER$
 */
/** @file:
 */

#ifndef ORTE_MCA_HDCLIENT_BASE_H
#define ORTE_MCA_HDCLIENT_BASE_H

/*
 * includes
 */
#include "orte_config.h"
//#include "orte/types.h"
//#include "orte/constants.h"
//
//#include "opal/class/opal_list.h"
//#include "opal/mca/event/event.h"
//
//#include "opal/mca/mca.h"

#include "orte/mca/hdclient/hdclient.h"


BEGIN_C_DECLS

/*
 * MCA Framework
 */
ORTE_DECLSPEC extern mca_base_framework_t orte_hdclient_base_framework;
/* select a component */
ORTE_DECLSPEC int orte_hdclient_base_select(void);

///*
// * globals that might be needed
// */
//typedef struct orte_hdclient_base_t {
//    orte_hdclient_base_module_t *active_module;
//} orte_hdclient_base_t;
//
//ORTE_DECLSPEC extern orte_hdclient_base_t orte_hdclient_base;

END_C_DECLS

#endif
