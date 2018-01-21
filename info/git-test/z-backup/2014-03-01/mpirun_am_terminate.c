#include "../mpirun_am.h"

extern int mpirun_am_terminate(TerminateRequestProto *request, TerminateResponseProto** responseProto)
{
	char* response_buf = NULL;
	int response_buf_len;

	if (0 != send_request_recv_response(request, "terminate", &response_buf, &response_buf_len)) {
		yarn_log_error("mpirun_am_terminate: send_request_recv_response : failed.");
		goto cleanup;
	}

	/* unpack response*/
	*responseProto = terminate_response_proto__unpack(NULL, response_buf_len, response_buf);
    if (!*responseProto) {
    	goto cleanup;
    }

	if (!response_buf) {
		free(response_buf);
	}
	return 0;

cleanup:
	if (!response_buf) {
		free(response_buf);
	}
	return -1;
}
