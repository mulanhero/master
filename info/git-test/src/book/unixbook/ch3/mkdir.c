/*
 * mkdir.c
 *
 *  Created on: Dec 2, 2012
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/**
 * #include <sys/stat.h>
       #include <sys/types.h>
       int mkdir(const char *pathname, mode_t mode);
       int rmdir(const char *pathname);
 */
int main(int argc, char** argv){
	char *dirname = "/home/caoj7/zgo/build/mydir";

	if(mkdir(dirname, 0700) < 0){  //mkdir
		if(errno == EEXIST){
			fprintf(stderr, "%s already existed. I will remove it, and mkdir again\n", dirname);
			if(rmdir(dirname) < 0){    //rmdir
				perror("ERROR: rmdir");
				exit(1);
			}
			if(mkdir(dirname, 0755) < 0){//with a different mode
				perror("ERROR: mkdir");
				exit(1);
			}
		}else{
			perror("ERROR: mkdir");
			exit(1);
		}
	}
	return 0;
}

