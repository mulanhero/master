#ifndef ORTED_ORTEDSERVICE_IPC_H_
#define ORTED_ORTEDSERVICE_IPC_H_

#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>

#include "opal/util/output.h"
#include "orted_ortedservice_constants.h"

extern int ortedservice_sd;

typedef struct proc_exitcode {
	int pid;
	int exitcode;
} proc_exitcode_t;

extern bool orted_ortedservice_ipc_readytorun(int orte_local_jobid);
extern int orted_ortedservice_ipc_report_proc_pid(int orte_local_jobid, int *pid_array, int pid_array_len);

extern int orted_ortedservice_ipc_report_proc_exitcode(int orte_local_jobid, proc_exitcode_t *proc_exitcode_array, int proc_exitcode_array_len);


//======================
extern int orted_ipc_send(char* buffer, long length);
extern int orted_ipc_recv(char** buffer, int* length);


#endif /* ORTED_ORTEDSERVICE_IPC_H_ */
