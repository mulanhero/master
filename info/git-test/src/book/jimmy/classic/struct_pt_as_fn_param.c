#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int jobid;
	char *request_nodelist;
}request_t;


typedef struct {
	int jobid;
	char *response_nodelist;
}response_t;



int allocate(const request_t *request, response_t **response)
{
	*response = (response_t *)malloc(sizeof(response_t));
	(*response)->jobid = request->jobid;
	(*response)->response_nodelist = strdup(request->request_nodelist);
	return 0;
}

int main(){
	request_t request;
	response_t *response;
	request.jobid = 123;
	request.request_nodelist = strdup("vm[1-3]");

	allocate(&request, &response);

	printf("response->jobid = %d\n", response->jobid);
	printf("response->response_nodelist = %s\n", response->response_nodelist);

	free(request.request_nodelist);
	free(response->response_nodelist);
	free(response);
	return 0;
}
