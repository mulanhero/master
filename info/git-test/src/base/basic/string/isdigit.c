/*
 * test.c
 *
 *  Created on: Nov 20, 2012
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_digit(char *str){
	int i;
	for(i = 0; i < strlen(str)+1; i++){
		if(isdigit((int)str[i]))
			putchar(str[i]);
	}
	putchar('\n');
}


int main(int argc, char **argv){
	char *str = "1-5";
	print_digit(str);
	return 0;
}
