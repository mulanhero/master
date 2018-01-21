#include <stdio.h>
#include <stdlib.h>

#include <time.h>

int main()
{	
	time_t now = time(NULL);
	printf("now = %ld\n", now);

	sleep(2);
	
	time_t now1_bak;
	time_t now1 = time(&now1_bak);
	printf("now1_bak = %ld, now1 = %ld\n", now1_bak, now1);
	
	printf("now1 - now = %ld\n", now1 - now );
	return 0;
}
