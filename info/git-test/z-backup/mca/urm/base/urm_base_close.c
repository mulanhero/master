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
 * $COPYRIGHT$
 * 
 * Additional copyrights may follow
 * 
 * $HEADER$
 */

#include "orte_config.h"
#include "orte/constants.h"

#include <stdio.h>

#include "opal/mca/mca.h"
#include "opal/mca/base/base.h"

#include "orte/mca/urm/base/base.h"

//#include "orte/mca/ras/base/ras_private.h"

int orte_urm_base_finalize(void)
{
    if (NULL != orte_urm_base.active_module) {
        orte_urm_base.active_module->finalize();
    }
    
    return ORTE_SUCCESS;
}


int orte_urm_base_close(void)
{
    /* Close all remaining available components (may be one if this is a
       Open RTE program, or [possibly] multiple if this is ompi_info) */

    mca_base_components_close(orte_urm_base.urm_output,
                              &orte_urm_base.urm_opened, NULL);

    /* Close the framework output */
    opal_output_close (orte_urm_base.urm_output);
    orte_urm_base.urm_output = -1;

    return ORTE_SUCCESS;
}
