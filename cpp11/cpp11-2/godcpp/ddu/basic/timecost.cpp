#include<sys/time.h>
#include <iostream>

int main()
{
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);

    for (int i = 0; i < 100; i++) {
        usleep(1000);
    }

    gettimeofday(&end, NULL);

    double cost = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec) / 1000000.0;
    std::cout << "cost:" << cost << std::endl;

    return 0;
}
