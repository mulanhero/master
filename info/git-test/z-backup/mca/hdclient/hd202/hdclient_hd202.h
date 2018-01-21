/*
 * Copyright (c) 2012      Los Alamos National Security, LLC.  All rights reserved.
 *
 * $COPYRIGHT$
 * 
 * Additional copyrights may follow
 * 
 * $HEADER$
 */

/**
 * @file
 * 
 */

#ifndef MCA_hdclient_hd202_EXPORT_H
#define MCA_hdclient_hd202_EXPORT_H

#include "orte_config.h"

#include "orte/mca/hdclient/hdclient.h"

BEGIN_C_DECLS

/*
 * Local Component structures
 */

ORTE_MODULE_DECLSPEC extern orte_hdclient_base_component_t mca_hdclient_hd202_component;

ORTE_DECLSPEC extern orte_hdclient_base_module_t orte_hdclient_hd202_module;

END_C_DECLS

#endif /* MCA_hdclient_hd202_EXPORT_H */
