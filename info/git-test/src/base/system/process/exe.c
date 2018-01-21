#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
#include <unistd.h>

       extern char **environ;

       int execl(const char *path, const char *arg, ...);
       int execlp(const char *file, const char *arg, ...);
       int execle(const char *path, const char *arg,
                  ..., char * const envp[]);
       int execv(const char *path, char *const argv[]);
       int execvp(const char *file, char *const argv[]);
       int execvpe(const char *file, char *const argv[],
                  char *const envp[]);
*/

int main()
{
	puts("e.g.: int execlp(const char *file, const char *arg, ...)");

	int rc;
	rc = execlp("ps", "ps", "-ef", NULL);

	if (rc != 0) {
		perror("execlp");
	}
	return 0;
}
