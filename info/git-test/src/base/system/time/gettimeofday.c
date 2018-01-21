#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() 
{
	struct timeval tv1, tv2;
	int rc;
	float timeused;

	if(0 != (rc = gettimeofday(&tv1, NULL))){
		perror("gettimeofday");
		exit(1);
	}

	usleep(5003000);

	if(0 != (rc = gettimeofday(&tv2, NULL))){
		perror("gettimeofday");
		exit(1);
	}

	timeused = ((tv2.tv_sec-tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec)) / (float)1000000;
	printf("timeused = %f (s)\n", timeused);

	return 0;
}
