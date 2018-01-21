#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main()
{
	char **tmp = environ;
	while (*tmp) {
		puts(*tmp);
		tmp++;
	}

	setenv("JIMMY_HOME", "XIAN", 1);
	printf("JIMMY_HOME = %s\n", getenv("JIMMY_HOME"));
	
	unsetenv("JIMMY_HOME");
	printf("JIMMY_HOME = %s\n", getenv("JIMMY_HOME"));
	return 0;
}
