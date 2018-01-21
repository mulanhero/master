#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Declare some global variables*/
int global_int1;
int global_int2=10;
char global_string[10];
const int const_int = 10;

void test1(void){
        global_int1 = 20;
        printf("[test1] global_int2 = %d\n",global_int2);
}

void test2(void){
        strcpy(global_string,"Hello");
        printf("[test2] global_int1 = %d\n",global_int1);
}

void test3(void){
        printf("[test3] global_string = %s\n",global_string);
}

int main(int argc, char **argv){
        test1();
        test2();
        test3();
        return 0;
}
