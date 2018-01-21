/*
 * if_ifdef_ifndef.c
 *
 *  Created on: Dec 16, 2012
 *      Author: caoj7
 */

#define _IPV4
#define DEBUG
#define UPPER   0

#ifdef _IPV4
#define LENGTH 32
#else
#define LENGTH 128
#endif

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int main(void){
    printf("LENGTH = %d\n", LENGTH);


#ifdef DEBUG
    perror("DEBUG is defined");
#endif


    int i, total = 0;
    for(i = 1; i  <= 10; i++){
#ifndef ADD
        total += i;
#else
        total *= i;
#endif
    }
    printf("total = %d\n", total);


    char *str = "ShangHai";
    int j;
    for(j = 0; j < strlen(str); j++)
#if UPPER
        putchar(toupper(str[j]));
#else
        putchar(tolower(str[j]));
#endif
        putchar('\n');
    return 0;
}

