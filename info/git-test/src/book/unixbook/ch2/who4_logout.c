/*
 * who4_logout.c
 *
 *  Created on: Nov 25, 2012
 *      Author: caoj7
 */
/**
 * sudo ./src/unix/ch2/who4
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utmp.h>
#include <unistd.h>
#include <time.h>



void who(){
	int fd;
	struct utmp entry;

	fd = open(UTMP_FILE, O_RDONLY);
	if(fd == -1){
		perror("ERROR: open");
		exit (1);
	}

	while(read(fd, &entry, sizeof(entry)) > 0){
		printf("%-8.8s	", entry.ut_name);
		printf("%-8.8s	", entry.ut_line);
		char *time_str = ctime(&entry.ut_tv.tv_sec);
		printf("%12.12s	", time_str+4);
		printf("(%s)\n", entry.ut_host);
	}

	close(fd);
}


void log_out(char *line){
	int fd;
	struct utmp entry;

	fd = open(UTMP_FILE, O_RDWR);
	if(fd == -1){
		perror("ERROR: open");
		exit (1);
	}

	while(read(fd, &entry, sizeof(entry)) > 0){
		if(strncmp(entry.ut_line, line, sizeof(entry.ut_line)) == 0){
			entry.ut_type = DEAD_PROCESS;
			strcpy(entry.ut_name, " ");
			entry.ut_tv.tv_sec = time(NULL);
//			time(&entry.ut_tv.tv_sec);  //equals to the above line
			lseek(fd, -sizeof(entry), SEEK_CUR);
			if(write(fd, &entry, sizeof(entry)) == -1){
				perror("write");
				exit (1);
			}
		}
	}
	close(fd);
}


int main(int argc, char *argv[]){
	who();
	log_out("pts/1");
	puts("======================================");
	who();
	return 0;
}
