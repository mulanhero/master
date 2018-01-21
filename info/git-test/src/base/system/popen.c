#include <stdio.h>
#include <stdlib.h>

/*
 *  FILE *popen(const char *command, const char *type);
 *  int pclose(FILE *stream);
 */
/*
 *  using popen in c to start a process then write to it using fprintf
 */
int main()
{
	FILE *fp;
	int i;

	fp = popen("cat", "w");
	if(fp == NULL){
		perror("popen");
		return -1;
	}

	for(i = 0; i < 10; i++){
		fprintf(fp, "popen_%d\n", i);
	}

	pclose(fp);
	return 0;
}
