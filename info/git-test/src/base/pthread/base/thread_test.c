#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int total = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* func(void* param)
{
	int i;
	for (i = 0; i < 100; i++) {
		pthread_mutex_lock(&mutex);
		total += *(int *)param;	
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main()
{
	pthread_t t1, t2;
	int param1 = 1;
	int param2 = 2;
	
	pthread_create(&t1, NULL, func, (void*)&param1);
	pthread_create(&t2, NULL, func, (void*)&param2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("total = %d\n", total);
	return 0;
}
