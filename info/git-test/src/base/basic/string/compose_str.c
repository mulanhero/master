/*
 * compose_str.c
 *
 *  Created on: Jan 28, 2013
 *      Author: caoj7
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argv.h"

#define SIZE 256

/*
 * gcc -g -Wall argv.c compose_str.c -o compose
 * ./compose
 */

int main()
{
	char *deallocate = "deallocate slurm_jobid=744 job_return_code=0:slurm_jobid=745 job_return_code=-1";
	char **jobid_argv = NULL, **tmp_jobid_argv;
	char *pos = NULL;
	uint32_t slurm_jobid;
	uint32_t job_return_code;

	char tmp_buf[SIZE];
	char total_buf[SIZE] = "";

	jobid_argv = argv_split(deallocate, ':');
	/* jobid_argv will be freed */
	tmp_jobid_argv = jobid_argv;
	while(*tmp_jobid_argv){
		puts(*tmp_jobid_argv);
		if(NULL != (pos = strstr(*tmp_jobid_argv, "slurm_jobid="))){
			pos = pos + strlen("slurm_jobid=");
			sscanf(pos, "%u", &slurm_jobid);
		}

		if(NULL != (pos = strstr(*tmp_jobid_argv, "job_return_code="))){
			pos = pos + strlen("job_return_code=");
			sscanf(pos, "%u", &job_return_code);
		}

		sprintf(tmp_buf, "slurm_jobid=%u job_rc = %d successful", slurm_jobid, job_return_code);
		if(0 == strlen(total_buf)){
			strcpy(total_buf, tmp_buf);
		}else{
			strcat(total_buf, ":");
			strcat(total_buf, tmp_buf);
		}

		tmp_jobid_argv++;
	}
	/* free jobid_argv */
	argv_free(jobid_argv);

	printf("haha: total_buf = %s\n", total_buf);

	return EXIT_SUCCESS;
}
