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
 * $COPYRIGHT$
 * 
 * Additional copyrights may follow
 * 
 * $HEADER$
 */

#include "orte_config.h"
#include "orte/constants.h"

#include "opal/mca/base/base.h"
#include "opal/mca/base/mca_base_param.h"

#include "orte/util/name_fns.h"
#include "orte/runtime/orte_globals.h"

//#include "orte/mca/ras/base/ras_private.h"
#include "urm_slurm.h"


/*
 * Local functions
 */
static int urm_slurm_open(void);
static int urm_slurm_close(void);
static int orte_urm_slurm_component_query(mca_base_module_t **module, int *priority);




orte_urm_slurm_component_t mca_urm_slurm_component = {
    {
        /* First, the mca_base_component_t struct containing meta
           information about the component itself */

        {
            ORTE_URM_BASE_VERSION_2_0_0,
        
            /* Component name and version */
            "slurm",
            ORTE_MAJOR_VERSION,
            ORTE_MINOR_VERSION,
            ORTE_RELEASE_VERSION,
        
            /* Component open and close functions */
            urm_slurm_open,
            urm_slurm_close,
            orte_urm_slurm_component_query
        },
        {
            /* The component is checkpoint ready */
            MCA_BASE_METADATA_PARAM_CHECKPOINT
        }
    }
};


static int urm_slurm_open(void)
{
    int seconds;
    /* Register an integer MCA parameter  */
    mca_base_param_reg_int(&mca_urm_slurm_component.super.base_version,
                           "dyn_allocate_timeout",
                           "Number of seconds to wait for Slurm dynamic allocation",
                           false, false, 30, &seconds);
    mca_urm_slurm_component.timeout.tv_sec = seconds;
    mca_urm_slurm_component.timeout.tv_usec = 0;

    mca_base_param_reg_int(&mca_urm_slurm_component.super.base_version,
                           "enable_dyn_alloc",
                           "Whether or not dynamic allocations are enabled",
                           false, false, (int)false, &seconds);
    mca_urm_slurm_component.dyn_alloc_enabled = OPAL_INT_TO_BOOL(seconds);

    mca_base_param_reg_string(&mca_urm_slurm_component.super.base_version,
                              "config_file",
                              "Path to Slurm configuration file",
                              false, false, NULL, &mca_urm_slurm_component.config_file);
    return ORTE_SUCCESS;
}

static int urm_slurm_close(void)
{
    if (NULL != mca_urm_slurm_component.config_file) {
        free(mca_urm_slurm_component.config_file);
    }
    return ORTE_SUCCESS;
}

static int orte_urm_slurm_component_query(mca_base_module_t **module, int *priority)
{
    /* if I built, then slurm support is available. If
     * I am not in a Slurm allocation, and dynamic alloc
     * is not enabled, then I'll deal with that by returning
     * an appropriate status code upon allocation
     */

    OPAL_OUTPUT_VERBOSE((2, orte_urm_base.urm_output,
                         "%s urm:slurm: available for selection",
                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME)));
    /* since only one RM can exist on a cluster, just set
     * my priority to something - the other components won't
     * be responding anyway
     */
    *priority = 50;
    *module = (mca_base_module_t *) &orte_urm_slurm_module;
    return ORTE_SUCCESS;
}
