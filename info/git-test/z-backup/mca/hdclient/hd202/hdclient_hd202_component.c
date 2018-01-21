/*
 * Copyright (c) 2012      Los Alamos National Security, LLC. All rights reserved.
 *
 * $COPYRIGHT$
 * 
 * Additional copyrights may follow
 * 
 * $HEADER$
 */

#include "orte_config.h"
#include "opal/util/output.h"

#include "orte/runtime/orte_globals.h"

#include "orte/mca/hdclient/hdclient.h"
#include "orte/mca/hdclient/base/base.h"
#include "hdclient_hd202.h"

/*
 * Public string for version number
 */
const char *orte_hdclient_hd202_component_version_string =
    "ORTE HDCLIENT hd202 MCA component version " ORTE_VERSION;

/*
 * Local functionality
 */
static int hdclient_hd202_register(void);
static int hdclient_hd202_open(void);
static int hdclient_hd202_close(void);
static int hdclient_hd202_component_query(mca_base_module_t **module, int *priority);

/*
 * Instantiate the public struct with all of our public information
 * and pointer to our public functions in it
 */
orte_hdclient_base_component_t mca_hdclient_hd202_component =
{
    /* Handle the general mca_component_t struct containing 
     *  meta information about the component
     */
    {
        ORTE_HDCLIENT_BASE_VERSION_2_0_0,
        /* Component name and version */
        "hd202",
        ORTE_MAJOR_VERSION,
        ORTE_MINOR_VERSION,
        ORTE_RELEASE_VERSION,
        
        /* Component open and close functions */
        hdclient_hd202_open,
        hdclient_hd202_close,
        hdclient_hd202_component_query,
        hdclient_hd202_register
    },
    {
        /* The component is checkpoint ready */
        MCA_BASE_METADATA_PARAM_CHECKPOINT
    },
};

static int hdclient_hd202_register(void)
{
    return ORTE_SUCCESS;
}


static int hdclient_hd202_open(void)
{
    return ORTE_SUCCESS;
}

static int hdclient_hd202_component_query(mca_base_module_t **module, int *priority)
{
	    *priority = 50;
	    *module = (mca_base_module_t *) &orte_hdclient_hd202_module;
	    return ORTE_SUCCESS;
}

static int hdclient_hd202_close(void)
{
    return ORTE_SUCCESS;
}
