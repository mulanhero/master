#include "../mpirun_am.h"

//static int generate_create_job_request(char *user, char** request_buf, int* request_buf_len)
//{
//	*request_buf = NULL;
//	CreateJobRequestProto request = CREATE_JOB_REQUEST_PROTO__INIT;
//    request.user = user;
//    *request_buf = generate_delimited_message((const ProtobufCMessage*)&request, request_buf_len);
//    if (!(*request_buf)) {
//    	return -1;
//    } else {
//    	return 0;
//    }
//}
//
//static int parse_create_job_response(char *response_buf, int response_buf_len, jobid_t **jobid)
//{
//	CreateJobResponseProto* responseProto = NULL;
//
//	if (!(responseProto = create_job_response_proto__unpack(NULL, response_buf_len, response_buf))) {
//		yarn_log_error("parse_create_job_response: create_job_response_proto__unpack failed");
//		goto rt_error;
//	}
//
//	*jobid = xmalloc(sizeof(jobid_t));
//	(*jobid)->timestamp = responseProto->jobid->timestamp;
//	(*jobid)->id = responseProto->jobid->id;
//
//	if (!responseProto) {
//		create_job_response_proto__free_unpacked(responseProto, NULL);
//	}
//	return 0;
//
//rt_error:
//	return -1;
//}


extern int mpirun_am_create_job(CreateJobRequestProto *request, CreateJobResponseProto** responseProto)
{
	char* response_buf = NULL;
	int response_buf_len;

	if (0 != send_request_recv_response(request, "create_job", &response_buf, &response_buf_len)) {
		yarn_log_error("mpirun_am_create_job: send_request_recv_response : failed.");
		goto cleanup;
	}

	/* unpack response*/
	*responseProto = create_job_response_proto__unpack(NULL, response_buf_len, response_buf);
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
