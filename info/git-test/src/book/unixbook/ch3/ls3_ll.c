/*
 * ls3_ll.c
 *
 *  Created on: Dec 1, 2012
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

void lsdir(char *dirname);
void ls_stat(char *dirname, char *filename);
char* xstrcat(char *dest, char *target);
void get_mode(struct stat *buf, char *mode, int size);

int main(int argc, char *argv[]){
	if(argc == 1)
		lsdir(".");
	else
		while(--argc){
			puts("===============");
			lsdir(*++argv);
		}

	return 0;
}

void lsdir(char *dirname){
	DIR *dir_pt;
	struct dirent *entry_pt;

	if(dir_pt = opendir(dirname), dir_pt == NULL){
		perror("ERROR: opendir");
		exit(1);
	}

	while(entry_pt = readdir(dir_pt), entry_pt != NULL)
		ls_stat(dirname, entry_pt->d_name);


	closedir(dir_pt);
}

void ls_stat(char *dirname, char *filename){
	char *tmp_dirname, *pathname;
	struct stat buf;
	char mode[11];
	char *time_str;
	char time[13];

	tmp_dirname = strdup(dirname);
	if(strcmp(tmp_dirname, "/") != 0)
		tmp_dirname = xstrcat(tmp_dirname, "/");
	pathname = xstrcat(tmp_dirname, filename);

//	puts(pathname);
	if(stat(pathname, &buf) < 0){
		perror("ERROR: stat");
		exit(1);
	}

	get_mode(&buf, mode, 11);
	printf("%s	", mode);
	printf("%d	", buf.st_nlink);
	printf("%s	", getpwuid(buf.st_uid)->pw_name);  //struct passwd *getpwuid(uid_t);
	printf("%s	", getgrgid(buf.st_gid)->gr_name);		//struct group *getgrgid(gid_t gid);
	printf("%ld	", buf.st_size);
//	printf("%s		", ctime(&buf.st_mtime));
	time_str = ctime(&buf.st_mtime);
	strncpy(time, time_str+4, 12);
	time[12] = 0;  //time[12] = '\0';
	printf("%s	", time);
//
	printf("%s\n", filename);
}


void get_mode(struct stat *buf, char *mode, int size){
	if(mode == NULL || size != 11)
		mode = (char *)malloc(11);
	strcpy(mode, "----------");

	if(S_ISDIR(buf->st_mode)) mode[0] = 'd';
	if(S_ISCHR(buf->st_mode)) mode[0] = 'c';
	if(S_ISBLK(buf->st_mode)) mode[0] = 'b';
	if(S_ISLNK(buf->st_mode)) mode[0] = 'l';
	if(S_ISSOCK(buf->st_mode)) mode[0] = 's';
	if(S_ISFIFO(buf->st_mode)) mode[0] = 'p';

	if(buf->st_mode & S_IRUSR) mode[1]= 'r';
	if(buf->st_mode & S_IWUSR) mode[2]= 'w';
	if(buf->st_mode & S_IXUSR) mode[3]= 'x';
	if(buf->st_mode & S_IRGRP) mode[4]= 'r';
	if(buf->st_mode & S_IWGRP) mode[5]= 'w';
	if(buf->st_mode & S_IXGRP) mode[6]= 'x';
	if(buf->st_mode & S_IROTH) mode[7]= 'r';
	if(buf->st_mode & S_IWOTH) mode[8]= 'w';
	if(buf->st_mode & S_IXOTH) mode[9]= 'x';
}

char* xstrcat(char *dest, char *target){
	char *ret;
	ret = (char *)malloc(strlen(dest) + strlen(target) + 1);
	strcpy(ret, dest);
	strcat(ret, target);
	return ret;
}
