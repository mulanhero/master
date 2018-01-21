/*
 * xstrcat.c
 *
 *  Created on: Dec 1, 2012
 *      Author: caoj7
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* xstrcat(char *dest, char *source){
	char *rt;
	rt = (char*)malloc(strlen(dest) + strlen(source) +1);
	strcpy(rt, dest);
	strcat(rt, source);
	return rt;
}

int main(int argc, char *argv[]){
	char *str1, *str2, *rt;
	str1 = "hello,";
	str2 = "world!";
	rt = xstrcat(str1, str2);
	puts(rt);
	return 0;
}
