#include <stdio.h>
#include <stdlib.h>
/*
 * A short example to show how to clear all enviroment variables
 * from a C program using the libc function clearenv.
 *
 * The  clearenv()  function  clears  the environment of all name-value pairs
 * and sets the value of the external variable environ to NULL.
 */
int main()
{
	int rc;

	system("env");
	puts("==================\n");
	rc = clearenv();
	if(rc != 0){
		perror("clearenv()");
		exit(-1);
	}
	system("env");
	return 0;
}
