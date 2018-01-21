/* -*- C -*-
 *
 * $HEADER$
 *
 * The most basic of MPI applications
 */

#include <stdio.h>
#include <stdlib.h>

#include "opal/util/argv.h"

#include "orte/util/proc_info.h"
#include "orte/mca/plm/plm.h"
#include "orte/mca/rml/rml.h"
#include "orte/mca/errmgr/errmgr.h"
#include "orte/runtime/runtime.h"
#include "orte/runtime/orte_globals.h"
#include "orte/util/name_fns.h"

#include "orte/mca/hdclient/hdclient.h"
#include "orte/mca/hdclient/base/base.h"

//export OMPI_MCA_test=xxx


int main(int argc, char* argv[])
{
    int rc, ret;
    char *error;

    setenv("OMPI_MCA_hdclient_base_verbose", "10", 1);
    printf("OMPI_MCA_hdclient_base_verbose = %s\n", getenv("OMPI_MCA_test_base_verbose"));

#if 1
    setenv("OMPI_MCA_hdclient", "hd202", 1);
    printf("OMPI_MCA_hdclient = %s\n", getenv("OMPI_MCA_hdclient"));
#endif

    if (0 > (rc = orte_init(&argc, &argv, ORTE_PROC_NON_MPI))) {
        fprintf(stderr, "couldn't init orte - error code %d\n", rc);
        return rc;
    }

    /* open and setup the state machine */
    if (ORTE_SUCCESS
            != (ret = mca_base_framework_open(&orte_hdclient_base_framework, 0))) {
        ORTE_ERROR_LOG(ret);
        error = "orte_hdclient_base_open";
        exit(1);
    }
    if (ORTE_SUCCESS != (ret = orte_hdclient_base_select())) {
        ORTE_ERROR_LOG(ret);
        error = "orte_hdclient_base_select";
        exit(1);
    }

	char *in = "jimmy";
	orte_hdclient.print(in);


    /* All done */
    orte_finalize();
    return 0;
}
