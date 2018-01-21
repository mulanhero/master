/*
===================================================
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
       int open(const char *pathname, int flags);
       int open(const char *pathname, int flags, mode_t mode);
       int creat(const char *pathname, mode_t mode);
       creat() is equivalent to open() with flags equal to O_CREAT|O_WRONLY|O_TRUNC.
====================================================
    	flags: O_RDONLY, O_WRONLY, or  O_RDWR //#include <fcntl.h>

    	The file creation flags: O_CREAT, O_EXCL, O_NOCTTY, and O_TRUNC
		The file status flags: O_APPEND, O_ASYNC, O_CREAT, O_DIRECT, O_DIRECTORY,...
		Some of these optional flags can be altered using fcntl() after the file has been opened.

		mode_t   //#include <sys/types.h>
		mode //#include <sys/stat.h>
		S_IRWXU  //00700 user (file owner) has read, write and execute permission
		S_IRUSR  //00400 user has read permission
		S_IWUSR  //00200 user has write permission
       	S_IXUSR  //00100 user has execute permission
=====================================================
#include <unistd.h>
       ssize_t read(int fd, void *buf, size_t count);
#include <unistd.h>
       int close(int fd);
=====================================================
*/
//struct utmp {
//            short ut_type;              /* type of login */
//            pid_t ut_pid;               /* PID of login process */
//            char ut_line[UT_LINESIZE];  /* device name of tty - "/dev/" */
//            char ut_id[4];              /* init id or abbrev. ttyname */
//            char ut_user[UT_NAMESIZE];  /* user name */
//            char ut_host[UT_HOSTSIZE];  /* hostname for remote login */
//            struct exit_status ut_exit; /* The exit status of a process
//                                           marked as DEAD_PROCESS */
//
//            /* The ut_session and ut_tv fields must be the same size when
//               compiled 32- and 64-bit.  This allows data files and shared
//               memory to be shared between 32- and 64-bit applications */
//          #if __WORDSIZE == 64 && defined __WORDSIZE_COMPAT32
//            int32_t ut_session;         /* Session ID, used for windowing */
//            struct {
//              int32_t tv_sec;           /* Seconds */
//              int32_t tv_usec;          /* Microseconds */
//            } ut_tv;                    /* Time entry was made */
//          #else
//             long int ut_session;        /* Session ID, used for windowing */
//             struct timeval ut_tv;       /* Time entry was made */
//          #endif
//
//            int32_t ut_addr_v6[4];       /* IP address of remote host */
//            char __unused[20];           /* Reserved for future use */
//          };

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utmp.h>

#define SHOWHOST

void showinfo(struct utmp *utmp_entry){
	printf("%-8.8s", utmp_entry->ut_user);
	printf("	") ;
	printf("%-8.8s", utmp_entry->ut_line);
	printf("	") ;
	printf("%10ld", utmp_entry->ut_tv.tv_sec);
	printf("	") ;
#ifdef SHOWHOST
	printf("(%s)", utmp_entry->ut_host);
#endif
	putchar('\n');
}

int who1(){
	int fd;
	struct utmp entry;
	ssize_t length = sizeof(struct utmp);

	if(fd = open(UTMP_FILE, O_RDONLY), fd == -1){ //UTMP_FILE is in #include<utmp.h>
		perror(UTMP_FILE);
		exit(1);
	}

	while(read(fd, &entry, length) == length)
		showinfo(&entry);

	close(fd);
	return 0;
}

int main(int argc, char **argv){
	who1();
	return 0;
}
