#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char target[256];
	char *tmp;

	char *origin="/var/lib/gphd/hadoop-yarn/cache/nm-local-dir/usercache/yarn/appcache/application_1400867067745_0586/filecache/10/hello";
	char *appid="application_1400867067745_0587";

	if (NULL == (tmp = strstr(origin, "application_"))) {
		perror("failed to strstr");
		exit(1) ;
	}

	strncpy(target, origin, tmp-origin);
	target[tmp-origin]='\0';

	if (NULL == (tmp = strchr(tmp, '/'))) {
		perror("strchr failed");
		exit(1);
	}

	sprintf(target, "%s%s%s", target, appid, tmp);
	puts(target);
	puts(origin);


	return 0;
}
