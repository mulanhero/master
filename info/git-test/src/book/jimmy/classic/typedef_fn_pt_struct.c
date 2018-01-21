#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct request_t{
	int jobid;
	char *request_nodelist;
};

typedef struct request_t request_t;

struct response_t{
	int jobid;
	char *response_nodelist;
};

typedef struct response_t response_t;

typedef int (*allocate_fn)(const request_t *request, response_t **response);

typedef int (*launch_fn)(int jobid);

struct fn_s_t{
	allocate_fn 	allocate;
	launch_fn 	launch;
};

typedef struct fn_s_t fn_s_t;

/*
fn_s_t fn={
	NULL,
	NULL
};
*/
//fn_s_t *fn_pt;
//fn_pt = &fn;

static int allocating(const request_t *request, response_t **response)
{
	*response = (response_t *)malloc(sizeof(response_t));
	(*response)->jobid = request->jobid;
	(*response)->response_nodelist = strdup(request->request_nodelist);
	return 0;
}

static int launching(int jobid)
{
	printf("jobid = %d is launching\n", jobid);
	return 0;
}

fn_s_t fn = {
	allocating,
	launching
};

//fn_pt = &fn2;

int main(){
 	request_t request;
	response_t *response;
	request.jobid = 123;
	request.request_nodelist = strdup("vm[1-3]");

	fn.allocate(&request, &response);
	printf("response->jobid = %d\n", response->jobid);
	printf("response->response_nodelist = %s\n", response->response_nodelist);

	free(request.request_nodelist);
	free(response->response_nodelist);
	free(response);

	fn.launch(456);

	return 0;
}
