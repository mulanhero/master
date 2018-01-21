#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int signum)
{
	puts("I am signal handler");
}

int main()
{
	pid_t pid;
	pid = fork();

	if(pid < 0) {
		perror("fork");
		exit(-1);
	}

	if (pid == 0) {
		puts("I am child");	
		kill(getppid(), SIGALRM);
	} else {
		puts("I am parents");	
		signal(SIGALRM, alarm_handler);
		pause();
	}

	return 0;
}
