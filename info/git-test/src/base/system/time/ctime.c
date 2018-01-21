#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    /*
     * time() returns the time as the number of seconds
     * since the Epoch, 1970-01-01 00:00:00 +0000 (UTC).
     */
	time_t now = time(NULL);
	if(-1 == now) {
		perror("time");
		exit(1);
	}

	char *now_str = ctime(&now);
	printf("now = %ld, now_str = %s\n", now, now_str);
	return 0;
}
