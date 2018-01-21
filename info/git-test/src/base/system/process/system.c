#include <stdio.h>
#include <stdlib.h>

int main()
{
	puts("system(\"ps -ef\")");
	int rc;

	sleep(3);
	rc = system("ps -ef");

	printf("rc = %d\n", rc);
	return 0;
}
