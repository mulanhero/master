/*
 * ls1.c
 *
 *  Created on: Nov 25, 2012
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <dirent.h>

/**
 * #include <sys/types.h>
 * #include <dirent.h>
       DIR *opendir(const char *name);
 *
 * struct dirent *readdir(DIR *dir);
 *
 * int closedir(DIR *dir);
 */

void lsdir(char *dirname){
	DIR *dir_ptr;
	struct dirent *entry_ptr;

	dir_ptr = opendir(dirname);
	if(dir_ptr == NULL){
		perror("ERROR: opendir");
		exit (1);
	}

	while(entry_ptr = readdir(dir_ptr), entry_ptr != NULL)
		puts(entry_ptr->d_name);

	closedir(dir_ptr);
}

int main(int argc, char *argv[]){
	if(argc == 1)
		lsdir(".");
	else {
//		int i;
//		for(i = 1; i < argc; i++){
//			puts("=================");
//			lsdir(argv[i]);
//		}
		while(--argc){
			puts("=================");
			lsdir(*++argv);
		}
	}
	return 0;
}

