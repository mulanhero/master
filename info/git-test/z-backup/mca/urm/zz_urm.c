/*
 * urm_test.c
 *
 *  Created on: Jan 18, 2013
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>

#include "orte/mca/urm/urm.h"
#include "orte/mca/urm/base/base.h"

int main(int argc, char *argv[])
{
	int rc;

	if (0 > (rc = orte_init(&argc, &argv, ORTE_PROC_NON_MPI))) {
		fprintf(stderr, "couldn't init orte - error code %d\n", rc);
		return rc;
	}

	int uid = 200;
	uint32_t jobid;
	char *resp = NULL;
	orte_urm_base_allocate(uid, &jobid, (void *)&resp);
	printf("jobid = %d, resp = %s\n", jobid, (char *)resp);
	if(resp)
		free(resp);

	 /* All done */
	    orte_finalize();

	return 0;
}

//void orte_urm_base_allocate(int uid, uint32_t *jobid, void **cbdata)
