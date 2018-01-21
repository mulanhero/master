#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "orted_ortedservice_ipc.h"
#include "orted_ortedservice_constants.h"
#include "str_utils.h"
#include "net_utils.h"


/* socket descriptor for orted to ortedservide */
int ortedservice_sd = -1;

/**
 * connect_to_server, return 0 if succeed
 */
static int connect_to_server(int socket_id, const char* host, int port)
{
    //define socket variables
    struct sockaddr_in serv_addr;
    struct hostent *server;

    //init port / socket / server
    server = gethostbyname(host);
    if (server == NULL)
    {
        opal_output(0, "orted_ortedservice_ipc:connect_to_server: ERROR, no such host.");
        return -1;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
                server->h_length);
    serv_addr.sin_port = htons(port);

    //connect via socket
    if (connect(socket_id, &serv_addr, sizeof(serv_addr)) < 0)
    {
        opal_output(0, "orted_ortedservice_ipc:connect_to_server: ERROR connecting.");
        return -1;
    }

    return 0;
}

/*
 * once setup the connection, send the HandShake_MSG first
 */
extern int orted_connect_to_ortedservice_ipc()
{
    int rc;

    // init socket
    ortedservice_sd = socket(AF_INET, SOCK_STREAM, 0);

    // read host/port
    char host[1024];
    rc = gethostname(host, 1023);
    char* port_str = getenv(OrtedServicePort_Key);
    if (!port_str || (0 != rc)) {
        opal_output(0, "orted_connect_to_ortedservice_ipc: failed to get host or port when trying to connect to ortedService");
        return -1;
    }
    int port = atoi(port_str);

    // connect to server
    rc = connect_to_server(ortedservice_sd, host, port);
    if (0 != rc) {
        opal_output(0, "orted_connect_to_ortedservice_ipc: connect to ortedService failed.");
        return -1;
    }

    // send handshake
    rc = write_all(ortedservice_sd, HandShake_MSG, strlen(HandShake_MSG));
    if (0 != rc) {
        opal_output(0, "orted_connect_to_ortedservice_ipc: send handshake to socket failed");
        return -1;
    }

    // recv handshake
    char recv[strlen(HandShake_MSG) + 1];
    rc = read_all(ortedservice_sd, recv, strlen(HandShake_MSG));
    if (0 != rc) {
        opal_output(0, "orted_connect_to_ortedservice_ipc: read handshake from socket failed");
        return -1;
    }
    recv[strlen(HandShake_MSG)] = '\0';

    // verify the handshake recved from
    if (0 != strcmp(HandShake_MSG, recv)) {
        opal_output(0, "orted_connect_to_ortedservice_ipc: failed to verify handshake from ortedService, read str is %s", recv);
        return -1;
    }

    return 0;
}


extern int orted_ipc_send(char* buffer, long length)
{
	int rc;
	// insanity check
	if (!buffer) {
		opal_output(0, "orted_ipc_send: a NULL buffer passed in, what happened?");
		return -1;
	}

	// pack message and send
	write_endian_swap_int(ortedservice_sd, length);
	rc = write_all(ortedservice_sd, buffer, length);
	if (rc != 0) {
		opal_output(0, "orted_ipc_send: failed to send buffer to ortedService");
		return -1;
	}

	return 0;
}


extern int orted_ipc_recv(char** buffer, int* length)
{
    int rc;
    int8_t success;
    int len = 0;

    rc = read_all(ortedservice_sd, &success, 1);
    if (0 != rc) {
        opal_output(0, "orted_ipc_recv: read success status from socket failed");
        return -1;
    }
    if (success == RT_Failed) {
        opal_output(0, "orted_ipc_recv: recved error response from ortedService");
        return -1;
    } else if (success != RT_Succeed) {
        opal_output(0, "orted_ipc_recv: recved unknown response from ortedService");
        return -1;
    }

    // read len from socket
    rc = read_all(ortedservice_sd, &len, sizeof(int));
    if (0 != rc) {
        opal_output(0, "orted_ipc_recv: read length from socket failed.");
        return -1;
    }
    len = int_endian_swap(len);

    // create buffer and read buffer
    *buffer = (char*)malloc(len);
    if (!*buffer) {
        opal_output(0, "orted_ipc_recv: failed to allocate memory for recv message");
        return -1;
    }
    rc = read_all(ortedservice_sd, *buffer, len);
    if (rc != 0) {
        opal_output(0, "orted_ipc_recv: failed to read response message from ortedService");
        free(*buffer);
        return -1;
    }

    *length = len;
    return 0;
}


extern bool orted_ortedservice_ipc_readytorun(int orte_local_jobid)
{
	char *send_buf = NULL;
	int send_len;

	char *recv_buf = NULL;
	int recv_len;
	int rc;

	//send
	if (-1 == asprintf(&send_buf, "%c%d", MsgType_ReadyToRun, orte_local_jobid)){
		opal_output(0, "orted_ortedservice_ipc_readytorun: allocate memory failed when asprintf");
		goto cleanup_rt_false;
	}
	send_len = strlen(send_buf);
	rc = orted_ipc_send(send_buf, send_len);
	if (rc != 0) {
		opal_output(0, "orted_ortedservice_ipc_readytorun: orted_ipc_send failed");
		goto cleanup_rt_false;
	}


	/*
	 * recv
	 */
	rc = orted_ipc_recv(&recv_buf, &recv_len);
	if (rc != 0) {
		opal_output(0, "orted_ortedservice_ipc_readytorun: orted_ipc_recv failed");
		goto cleanup_rt_false;
	}

	//verify if ready
	if (recv_len ==  1 && *recv_buf == Ready) {
		if (send_buf) {
			free(send_buf);
		}
		if (recv_buf) {
			free(recv_buf);
		}
		return true;
	}

cleanup_rt_false:
	if (send_buf) {
		free(send_buf);
	}
	if (recv_buf) {
		free(recv_buf);
	}
	return false;
}


/**
 * send msg format:  orte_local_jobid=12344:pid=12:pid=34:pid=56
 */

extern int orted_ortedservice_ipc_report_proc_pid(int orte_local_jobid, int *pid_array, int pid_array_len)
{
	char *send_buf = NULL;
	int send_len;

	char *recv_buf = NULL;
	int recv_len;
	int rc;
	int i;

	char *tmp_buf = NULL;

	//construct the send_buf
	if (-1 == asprintf(&send_buf, "%corte_local_jobid=%d", MsgType_ReportPIDs, orte_local_jobid)){
		opal_output(0, "orted_ortedservice_ipc_report_proc_pid: allocate memory failed when asprintf");
		goto cleanup_rt_failed;
	}

	for (i = 0; i < pid_array_len; i++) {
		if (-1 == asprintf(&tmp_buf, "%s:pid=%d", send_buf, pid_array[i])){
			opal_output(0, "orted_ortedservice_ipc_report_proc_pid: allocate memory failed when asprintf");
			goto cleanup_rt_failed;
		}

		if (send_buf) {
			free(send_buf);
		}
		send_buf = strdup(tmp_buf);
		if (tmp_buf) {
			free(tmp_buf);
			tmp_buf = NULL;
		}
	}

	//send
	send_len = strlen(send_buf);
	rc = orted_ipc_send(send_buf, send_len);
	if (rc != 0) {
		opal_output(0, "orted_ortedservice_ipc_report_proc_pid: orted_ipc_send failed");
		goto cleanup_rt_failed;
	}

	//recv
	rc = orted_ipc_recv(&recv_buf, &recv_len);
	if (rc != 0 || recv_len != 0) {
		opal_output(0, "orted_ortedservice_ipc_report_proc_pid: orted_ipc_recv failed");
		goto cleanup_rt_failed;
	}

	/**
	 * because we know if RT_Succeed, the above recv_len will be 0,
	 * so here afterorted_ipc_recv functions, we check nothing
	 *
	 */
	if (tmp_buf) {
		free(tmp_buf);
	}
	if (send_buf) {
		free(send_buf);
	}
	if (recv_buf) {
		free(recv_buf);
	}
	return 0;

cleanup_rt_failed:
	if (tmp_buf) {
		free(tmp_buf);
	}
	if (send_buf) {
		free(send_buf);
	}
	if (recv_buf) {
		free(recv_buf);
	}
	return -1;
}


/**
 * send msg format: orte_local_jobid=12344:pid=12,exitcode=0:pid=34,exitcode=-1
 */
extern int orted_ortedservice_ipc_report_proc_exitcode(int orte_local_jobid, proc_exitcode_t *proc_exitcode_array, int proc_exitcode_array_len)
{
	char *send_buf = NULL;
	int send_len;

	char *recv_buf = NULL;
	int recv_len;
	int rc;
	int i;

	char *tmp_buf = NULL;

	//construct the send_buf
	if (-1 == asprintf(&send_buf, "%corte_local_jobid=%d", MsgType_ReportProcExitCode, orte_local_jobid)){
		opal_output(0, "orted_ortedservice_ipc_report_proc_exitcode: allocate memory failed when asprintf");
		goto cleanup_rt_failed;
	}

	for (i = 0; i < proc_exitcode_array_len; i++) {
		if (-1 == asprintf(&tmp_buf, "%s:pid=%d,exitcode=%d", send_buf, proc_exitcode_array[i].pid, proc_exitcode_array[i].exitcode)){
			opal_output(0, "orted_ortedservice_ipc_report_proc_exitcode: allocate memory failed when asprintf");
			goto cleanup_rt_failed;
		}

		if (send_buf) {
			free(send_buf);
		}
		send_buf = strdup(tmp_buf);
		if (tmp_buf) {
			free(tmp_buf);
			tmp_buf = NULL;
		}
	}
	//send
	send_len = strlen(send_buf);
	rc = orted_ipc_send(send_buf, send_len);
	if (rc != 0) {
		opal_output(0, "orted_ortedservice_ipc_report_proc_exitcode: orted_ipc_send failed");
		goto cleanup_rt_failed;
	}

	//recv
	rc = orted_ipc_recv(&recv_buf, &recv_len);
	if (rc != 0 || recv_len != 0) {
		opal_output(0, "orted_ortedservice_ipc_report_proc_exitcode: orted_ipc_recv failed");
		goto cleanup_rt_failed;
	}

	/**
	 * because we know if RT_Succeed, the above recv_len will be 0,
	 * so here afterorted_ipc_recv functions, we check nothing
	 *
	 */
	if (tmp_buf) {
		free(tmp_buf);
	}
	if (send_buf) {
		free(send_buf);
	}
	if (recv_buf) {
		free(recv_buf);
	}
	return 0;

cleanup_rt_failed:
	if (tmp_buf) {
		free(tmp_buf);
	}
	if (send_buf) {
		free(send_buf);
	}
	if (recv_buf) {
		free(recv_buf);
	}
	return -1;
}










































