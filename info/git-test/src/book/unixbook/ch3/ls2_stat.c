/**
 * #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>

       int stat(const char *path, struct stat *buf);
       int fstat(int filedes, struct stat *buf);
       int lstat(const char *path, struct stat *buf);
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#include <time.h>

void lsdir(char *dirname);
void ls_stat(char *dirname, char *entry_name);

int main(int argc, char **argv){
	if(argc == 1)
		lsdir(".");
	else
		while(--argc){
			puts("=================");
			lsdir(*++argv);
		}

	return 0;
}

void lsdir(char *dirname){
	DIR *dir_ptr;
	struct dirent *entry_ptr;

	if(dir_ptr = opendir(dirname), dir_ptr == NULL){
		perror("ERROR: opendir");
		exit(1);
	}

	while(entry_ptr = readdir(dir_ptr), entry_ptr != NULL){
		puts(entry_ptr->d_name);
		ls_stat(dirname, entry_ptr->d_name);
	}

	closedir(dir_ptr);
}

/**
 *  #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>

       int stat(const char *path, struct stat *buf);
       int fstat(int filedes, struct stat *buf);
       int lstat(const char *path, struct stat *buf);


       struct stat {
              dev_t     st_dev;     // ID of device containing file
              ino_t     st_ino;     // inode number
              mode_t    st_mode;    // protection
              nlink_t   st_nlink;   // number of hard links
              uid_t     st_uid;     // user ID of owner
              gid_t     st_gid;     // group ID of owner
              dev_t     st_rdev;    // device ID (if special file)
              off_t     st_size;    // total size, in bytes
              blksize_t st_blksize; // blocksize for filesystem I/O
              blkcnt_t  st_blocks;  // number of blocks allocated
              time_t    st_atime;   // time of last access
              time_t    st_mtime;   // time of last modification
              time_t    st_ctime;   // time of last status change
          };

 */
void ls_stat(char *dirname, char *entry_name){
	struct stat buf;
	char *tmp_dirname, *path_name;

	tmp_dirname = strdup(dirname);
	if(strcmp(dirname, "/") != 0)
		strcat(tmp_dirname, "/");
	path_name = strcat(tmp_dirname, entry_name);

	if(stat(path_name, &buf) < 0){
		perror("ERROR: stat");
		exit (1);
	}

//	char *time_str = ctime(&buf.st_mtime);
	printf("mode_t = %d,  nlink_t = %d,  uid_t = %d, gid_t = %d, off_t = %d, time_t = %d\n",
			buf.st_mode, buf.st_nlink, buf.st_uid, buf.st_gid, buf.st_size, buf.st_mtime);
}

