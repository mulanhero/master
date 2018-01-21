#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int total = 0;

void* func(void* param)
{
    int i;
    for (i = 0; i < 100; i++) {
        pthread_mutex_lock(&mutex);
        total += *(int*) param;
        printf("total=%d\n", total);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    int p1 = 1, p2 = 2;

    pthread_create(&t1, NULL, func, &p1);
    pthread_create(&t2, NULL, func, &p2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("total = %d\n", total);
    return 0;
}
