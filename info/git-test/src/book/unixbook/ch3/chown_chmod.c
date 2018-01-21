/*
 *  #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

       int open(const char *pathname, int flags);
       int open(const char *pathname, int flags, mode_t mode);
       int creat(const char *pathname, mode_t mode);

		int chmod(const char *path, mode_t mode);
		mode_t umask(mode_t mask);

       	int chown(const char *path, uid_t owner, gid_t group);

		#include <sys/types.h>
        #include <utime.h>
       int utime(const char *filename, const struct utimbuf *buf);
       struct utimbuf {
                  time_t actime;       // access time
                  time_t modtime;      // modification time
              };

 	 int rename(const char *oldpath, const char *newpath);
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <time.h>

int main(int argc, char *argv[])
{
	char *filename = "/home/caoj7/zgo/build/test.txt";

	umask(0011);  //

	if(creat(filename, 0755) < 0){  //0755 & ~0011 = rwxr--r--  //creat
		perror("ERROR: creat");
		exit(1);
	}


	if(chmod(filename, 02600) < 0){ //rw---S---  //chmod
		perror("ERROR: chmod");
		exit(1);
	}



	if(chown(filename, 500, 500) < 0){ //the same as  //chown
		perror("ERROR: chown");
		exit(1);
	}

	struct utimbuf time_buf;
	time_t now_time;
	time(&now_time);
	time_buf.actime = now_time;
	time_buf.modtime = now_time;
	if(utime(filename, &time_buf) < 0){ //utime
		perror("ERROR: utime");
		exit(1);
	}


	if(rename(filename, "/home/caoj7/zgo/build/changedname2.txt") < 0){//rename
		perror("ERROR: rename");
		exit(1);
	}
	return 0;
}
