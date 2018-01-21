/*
 * ls4_ll.c
 *
 *  Created on: Dec 2, 2012
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void lsdir(char *dirname);
void ls_stat(char *dirname, char *entryname);
char* xstrcat(char *str1, char *str2);
void get_mode(struct stat *buf, char *mode);
char *uid2name(uid_t uid);
char *gid2name(gid_t gid);

int main(int argc, char *argv[])
{
	if(argc == 1)
		lsdir(".");
	else
		while(--argc)
			lsdir(*++argv);
	return 0;
}

void lsdir(char *dirname)
{
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

void ls_stat(char *dirname, char *entryname)
{
	char *tmp_pathname;
	struct stat buf;
	char mode[11];

	tmp_pathname = strdup(dirname);
	if(strcmp(dirname, "/") != 0)
		tmp_pathname = xstrcat(tmp_pathname, "/");
	tmp_pathname = xstrcat(tmp_pathname, entryname);

	if(stat(tmp_pathname, &buf) < 0){
		perror("ERROR: stat");
		exit(1);
	}

	get_mode(&buf, mode);
	printf("%s	", mode);
	printf("%d	", buf.st_nlink);

	printf("%s	", uid2name(buf.st_uid));
	printf("%s	", gid2name(buf.st_gid));
	printf("%ld	", buf.st_size);
	printf("%.12s	", ctime(&buf.st_mtime)+4);
	printf("%s\n", entryname);
}

char *uid2name(uid_t uid)
{
	static char str[20];  //static is important
	struct passwd *pwd;
	pwd = getpwuid(uid); //struct passwd *getpwuid(uid_t);
	if(pwd == NULL){
		sprintf(str, "%d", uid);
		return str;
	}else
		return	pwd->pw_name;

}

char *gid2name(gid_t gid)
{
	static char str[20];  //static is important
	struct group *grp;
	grp = getgrgid(gid);  //struct group *getgrgid(gid_t gid);
	if(grp == NULL){
		sprintf(str, "%d", gid);
		return str;
	}else
		return grp->gr_name;

}

void get_mode(struct stat *buf, char *mode)
{
	strcpy(mode, "----------");
	if(S_ISDIR(buf->st_mode)) mode[0] = 'd';
	if(S_ISCHR(buf->st_mode)) mode[0] = 'c';
	if(S_ISBLK(buf->st_mode)) mode[0] = 'b';

	if(S_IRUSR & buf->st_mode) mode[1] = 'r';
	if(S_IWUSR & buf->st_mode) mode[2] = 'w';
	if(S_IXUSR & buf->st_mode) mode[3] = 'x';
	if(S_IRGRP & buf->st_mode) mode[4] = 'r';
	if(S_IWGRP & buf->st_mode) mode[5] = 'w';
	if(S_IXGRP & buf->st_mode) mode[6] = 'x';
	if(S_IROTH & buf->st_mode) mode[7] = 'r';
	if(S_IWOTH & buf->st_mode) mode[8] = 'w';
	if(S_IXOTH & buf->st_mode) mode[9] = 'x';
//	S_ISUID    0004000   set UID bit
//	S_ISGID    0002000   set-group-ID bit (see below)
//	S_ISVTX    0001000   sticky bit (see below)
	if(S_ISUID & buf->st_mode) mode[3] = 's';
	if(S_ISGID & buf->st_mode) mode[6] = 's';
	if(S_ISVTX & buf->st_mode) mode[9] = 't';
	//if a directory has sticky, like /tmp, files in this
	//directory may only be deleted by their owners
}

char* xstrcat(char *str1, char *str2)
{
	char *rt;
	rt = (char *)malloc(strlen(str1) + strlen(str2) + 1);
	strcpy(rt, str1);
	strcat(rt, str2);
	return rt;
}
