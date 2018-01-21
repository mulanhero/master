#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

/* Redirect stdout to this file pointer.
   This is the central hack for this program.
 */
void redirectStdout(int to_fd) {
	int stdout_fd=1;
	if (-1==dup2(to_fd,stdout_fd)) {perror("dup2 stdout"); exit(1);}
}

/* Return true if this socket is readable right now.
  (Poor man's non-blocking I/O). */
int readable(int fd) {
	fd_set read;
	struct timeval to;
	to.tv_sec=0; to.tv_usec=0;
	FD_ZERO(&read);
	FD_SET(fd,&read);
	if (-1==select(fd+1,&read,NULL,NULL,&to))
		return 0; /* timeout */
	return FD_ISSET(fd,&read)?1:0;
}

/* Can read stuff written to stdout from this fd */
int readStdout;

/* Clean out the stdout pipe */
int readPipes(void) {
	char buf[1001];
	int ret;
	if (!readable(readStdout)) return 0;
	ret=read(readStdout,buf,1000);
	if (ret>0) {
	  buf[ret]=0;
	  fprintf(stderr,"--- Read from stdout (%d bytes) ---\n"
	  		"%s"
			"---\n",ret,buf);
	}
	return 1;
}

int main() {
	/* Set up our stdout socket: */
	int pair[2];
	if (-1==pipe(pair)) {perror("pipe stdout"); exit(1);}
	readStdout=pair[0];
	redirectStdout(pair[1]);

	/* Test it out */
	fprintf(stderr,"Doing some printfs...\n");
	printf("Hello, world!\n"); /*Shows nothing*/
	printf("Yes, it works!\n");
	fflush(stdout);
	fprintf(stderr,"Printfs all returned: reading pipes.\n");

	/* Write the output */
	while (readPipes()) {}

	return 0;
}
