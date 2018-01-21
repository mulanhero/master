#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid;

	if (0 > (pid = fork())){
		perror("fork");
		exit(1);
	}

	if (pid == 0) {
		puts("I am child!");
		char *argv[] = {"/bin/ls", "-l", "/", NULL};
		execv("/bin/ls", argv);
	} else {
		puts("I am parents");
		int status;
		wait(&status);

		if (WIFEXITED(status)) {
			printf("exited, status=%d\n", WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			printf("killed by signal %d\n", WTERMSIG(status));
		} else if (WIFSTOPPED(status)) {
			printf("stopped by signal %d\n", WSTOPSIG(status));
		} else if (WIFCONTINUED(status)) {
			printf("continued\n");
		}
	}
	return 0;
}
