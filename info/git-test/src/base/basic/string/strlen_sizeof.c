/*
 * strlen_sizeof.c
 *
 *  Created on: Dec 2, 2012
 *      Author: caoj7
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void test1(char *str){
	printf("%d\n", sizeof(str));
	printf("%d\n", strlen(str));
}

void test2(char str[]){
	printf("%d\n", sizeof(str));
	printf("%d\n", strlen(str));
}


int main(void) {
	char *str;
	str = "Hello,World!";
	printf("%d\n", sizeof(str));
	printf("%d\n", strlen(str));
	test1(str);
	test2(str);
	puts("===============");
	char char_array[20] = "Hello,World!";
	test1(char_array);
	test2(char_array);
	printf("%d\n", sizeof(char_array));
	printf("%d\n", strlen(char_array));
	return EXIT_SUCCESS;
}
