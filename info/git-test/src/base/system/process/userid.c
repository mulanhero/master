#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

int main()
{
	pid_t pid, ppid;
	printf("pid = %d\n", getpid());
	printf("ppid = %d\n", getppid());

	uid_t uid, euid;
	printf("uid = %d\n", getuid());
	printf("euid = %d\n", geteuid());
	
	gid_t gid, egid;
	printf("gid = %d\n", getgid());
	printf("egid = %d\n", getegid());

	struct passwd *pw;
	if (!(pw = getpwuid(getuid()))) {
		perror("getpwuid");
		exit(1);
	}
	
	printf("username = %s\n", pw->pw_name);
	printf("passwd = %s\n", pw->pw_passwd);
	printf("pw_uid = %d\n", pw->pw_uid);
	printf("pw_gid = %d\n", pw->pw_gid);
	printf("pw_gecos(real name) = %s\n", pw->pw_gecos);
	printf("pw_dir(home dir) = %s\n", pw->pw_dir);
	printf("pw_shell = %s\n", pw->pw_shell);

	return 0;

}
