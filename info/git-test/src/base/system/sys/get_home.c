#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

/*
 * The simple method is to pull the enviroment variable "HOME"
 */
int get_home_from_env()
{
	char *homedir;

	homedir = getenv("HOME");
	if(homedir == NULL){
		perror("getenv");
		return -1;
	}

	printf("HOME = %s\n", homedir);
	return 0;
}

/*
 * struct passwd *getpwuid(uid_t uid);
 * The slightly more complex method is to read it from the system user database.
 */
int get_home_from_pswd()
{
	struct passwd *pswd;
	uid_t uid;

	uid = getuid();
	pswd = getpwuid(uid);
	if(pswd == NULL){
		perror("getpwuid");
		return -1;
	}

	printf("HOME = %s\n", pswd->pw_dir);

	return 0;
}

int main()
{
	get_home_from_env();
	get_home_from_pswd();
	return 0;
}
