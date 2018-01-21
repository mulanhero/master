/*
 * who_buffer.c
 *
 *  Created on: Nov 24, 2012
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utmp.h>

#define SHOWHOST
#define SIZE 16

void showinfo(struct utmp entry[], int count){
	printf("===============count = %d====================\n", count);
	int i;
	for(i = 0; i < count; i++) {
		//if(entry[i].ut_type != USER_PROCESS)
		//	continue;
		printf("%8.8s	", entry[i].ut_user);
		printf("%8.8s	", entry[i].ut_line);

		char *time_ptr = ctime(&entry[i].ut_tv.tv_sec);
		printf("%12.12s	", time_ptr+4);
#ifdef SHOWHOST
		printf("(%s)", entry[i].ut_host);
#endif
		putchar('\n');
	}
}


void who(){
	int fd, count;
	struct utmp entry_array[SIZE];

	fd = open(UTMP_FILE, O_RDONLY);
	if(fd == -1){
		perror("open");
		exit(1);
	}
	int i = 0;
	while(count = read(fd, entry_array, sizeof(struct utmp) * SIZE) / sizeof(entry_array[0]), count > 0){
		printf("count = %d,i = %d\n", count, i++);
		showinfo(entry_array, count);
	}

	close(UTMP_FILE);
}

int main(int argc, char *argv[]){
	who();
	return 0;
}


