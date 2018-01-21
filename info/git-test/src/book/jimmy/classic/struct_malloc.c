#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int jobid;
	char *request_resource;
}request_t;

typedef struct{
	int jobid;
	char *response_resource;
}response_t;


int main()
{
	request_t *request;
	request = (request_t*)malloc(sizeof(request_t));
	/* request->jobid !!! not *request->jobid */
	request->jobid = 10;
	request->request_resource = strdup("node[1-2]");

	printf("request->jobid = %d\n", request->jobid);
	printf("request->request_resource = %s\n", request->request_resource);

	free(request->request_resource);
	free(request);

	return 0;
}
