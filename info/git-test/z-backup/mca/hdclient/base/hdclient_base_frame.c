#include "orte_config.h"
#include "orte/constants.h"

#ifdef HAVE_STRING_H
#include <string.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#include "opal/mca/mca.h"
#include "opal/mca/base/base.h"
#include "opal/mca/base/mca_base_param.h"

#include "opal/util/opal_environ.h"
#include "opal/util/output.h"
#include "opal/util/trace.h"
#include "opal/util/output.h"

#include "orte/util/show_help.h"
#include "orte/mca/hdclient/base/base.h"

/*
 * The following file was created by configure.  It contains extern
 * statements and the definition of an array of pointers to each
 * module's public mca_base_module_t struct.
 */

#include "orte/mca/hdclient/base/static-components.h"

/*
 * Global variables
 */
//orte_hdclient_base_t orte_hdclient_base;    //to be initialized when open


/*
 * The default module
 */
orte_hdclient_base_module_t orte_hdclient = {
    NULL,
    NULL,
    NULL
};


static int orte_hdclient_base_close(void)
{
    /* Close selected component */
//    if (NULL != orte_hdclient_base.active_module) {
//        orte_hdclient_base.active_module->finalize();
//    }

    if (NULL != orte_hdclient.finalize) {
        orte_hdclient.finalize();
    }

    return mca_base_framework_components_close(&orte_hdclient_base_framework, NULL);
}



/**
 *  * Function for finding and opening either all MCA components, or the one
 *   * that was specifically requested via a MCA parameter.
 *    */
static int orte_hdclient_base_open(mca_base_open_flag_t flags)
{
//    /* set default flags */
//    orte_hdclient_base.active_module = NULL;

    /* Open up all available components */
    return mca_base_framework_components_open(&orte_hdclient_base_framework, flags);
}

MCA_BASE_FRAMEWORK_DECLARE(orte, hdclient, "ORTE Hadoop Client",
                           NULL, orte_hdclient_base_open, orte_hdclient_base_close,
                           mca_hdclient_base_static_components, 0);
