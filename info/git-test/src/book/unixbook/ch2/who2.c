/**
 * based who1.c, we need to revise it on two aspects:
 * 1)	remove the blank records
 * 2)	get the correct log-in time
 */
/*
 * //man -k time|grep convert
 * #include <time.h>
       char *asctime(const struct tm *tm);
       char *asctime_r(const struct tm *tm, char *buf);
       char *ctime(const time_t *timep);
 */

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utmp.h>

#include <time.h>

#define SHOWHOST



void showinfo(struct utmp *utmp_entry){
	if(utmp_entry->ut_type != USER_PROCESS)
		return;    //delete non-user login

	printf("%-8.8s", utmp_entry->ut_user);
	printf("	") ;
	printf("%-8.8s", utmp_entry->ut_line);
	printf("	") ;
	//convert a time value to a date and time string
    char *time_ptr = ctime(&utmp_entry->ut_tv.tv_sec);
	printf("%12.12s", time_ptr+4);
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
