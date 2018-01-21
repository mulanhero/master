#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main()
{
	int fd[2];
	int rc, pid;

	if (0 > (rc = pipe(fd))) {
		perror("pipe");
		exit(1);
	}

	if (0 > (pid = fork())) {
		perror("fork");
		exit(1);
	}

	if (pid > 0) {
		puts("I am parents");
		close(fd[0]);
		write(fd[1], "hello, my son", strlen("hello, my son"));
		wait(NULL);
	} else {
	
		puts("I am child.");
		close(fd[1]);

		char buf[1024];
		memset(buf, 0, 1024);
		read(fd[0], buf, 1024);
		puts(buf);
	}
	return 0;
}
