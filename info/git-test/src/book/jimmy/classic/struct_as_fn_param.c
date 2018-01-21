#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int id;
	char *request_nodelist;
}request_t;

typedef struct{
	int id;
	char *allocate_nodelist;
}response_t;

void free_request(request_t *request)
{	
	free(request->request_nodelist);
}

void free_response(response_t *response)
{
	free(response->allocate_nodelist);
}

int allocate(request_t *request, response_t *response)
{
	printf("request->id = %d\n", request->id);
	printf("request->request_node = %s\n", request->request_nodelist);

	response->id = request->id;
	response->allocate_nodelist = strdup("vm[99-100]");
	return 0;
}

int main()
{
	request_t request;
	response_t response;

	request.id = 555;
	request.request_nodelist = strdup("vm[1-3]");

	allocate(&request, &response);

	printf("response.id = %d\n", response.id);
	printf("response.allocate_nodelist = %s\n", response.allocate_nodelist);

	free_request(&request);
	free_response(&response);
	return 0;
}
