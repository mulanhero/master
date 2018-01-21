#include "orte_config.h"
#include "orte/constants.h"

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "opal/mca/mca.h"
#include "opal/mca/base/base.h"
#include "opal/mca/base/mca_base_param.h"
#include "opal/util/output.h"

#include "orte/mca/hdclient/base/base.h"

/*
 * Select one hdclient component from all those that are available.
 */
int orte_hdclient_base_select(void)
{
    /* For all other systems, provide the following support */

    orte_hdclient_base_component_t *best_component = NULL;
    orte_hdclient_base_module_t *best_module = NULL;

    /*
     * Select the best component
     */
    if( OPAL_SUCCESS != mca_base_select("hdclient", orte_hdclient_base_framework.framework_output,
                                        &orte_hdclient_base_framework.framework_components,
                                        (mca_base_module_t **) &best_module,
                                        (mca_base_component_t **) &best_component) ) {
        /* This will only happen if no component was selected */
        /* If we didn't find one to select, that is okay */
        return ORTE_SUCCESS;
    }

    /* Save the winner */
    orte_hdclient = *best_module;

    if (NULL != orte_hdclient.init) {
        return orte_hdclient.init();
    }

//    orte_hdclient_base.active_module = best_module;
//    if (NULL != orte_hdclient_base.active_module->init) {
//        return orte_hdclient_base.active_module->init();
//    }

    return ORTE_SUCCESS;
}
