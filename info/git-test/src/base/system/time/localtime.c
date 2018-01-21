#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 40

int main()
{

    time_t now;
    struct tm *tm;
    char time_buf[SIZE];

    now = time(NULL);
    tm = localtime(&now);
    strftime(time_buf, SIZE, "%d %B %Y %I:%M:%S %p", tm);
    printf("%s\n", time_buf);
    return 0;
}
