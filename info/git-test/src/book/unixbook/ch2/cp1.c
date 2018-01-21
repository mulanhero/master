/*
 * cp1.c
 *
 *  Created on: Nov 24, 2012
 *      Author: caoj7
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define SIZE 256
#define MODE 0644

void cp(char *src_file, char *target_file){
	int src_fd, target_fd;
	char buf[SIZE];
	int count;

	src_fd = open(src_file, O_RDONLY);
	if(src_fd == -1){
		perror("open");
		exit(1);
	}

	target_fd =	creat(target_file, MODE);
	if(target_fd == -1){
		perror("creat");
		exit(1);
	}

	while(count = read(src_fd, buf, SIZE), count > 0){
		if(write(target_fd, buf, count) != count){
			perror("write");
			exit(1);
		}
	}

	close(src_fd);
	close(target_fd);
}


int main(int argc, char* argv[]){
	if(argc != 3){
		puts("input parameter error, should be like cp1 file1 file2");
		exit (1);
	}
	cp(argv[1], argv[2]);
	return 0;
}
