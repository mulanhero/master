#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void action_func()
{
	puts("2 seconds has passed by....");
}


void init_sigaction()
{
	struct sigaction act;
	act.sa_handler = action_func;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGPROF, &act, NULL);
}


int main()
{
	init_sigaction();

	struct itimerval itv;
	itv.it_value.tv_sec = 2;
	itv.it_value.tv_usec = 0;
	itv.it_interval = itv.it_value;
	setitimer(ITIMER_PROF, &itv, NULL);
	/*1. when time is up, 'ITIMER_PROF signal will be triggered '*/
	/*2. when SIGPROF is triggered, 'action_func' will be invoked */

	while (1) ;

	return 0;
}
