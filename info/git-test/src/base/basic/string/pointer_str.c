/*
 * pointer.c
 *
 *  Created on: Nov 17, 2012
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>

void point_argv(int argc, char **argv){
	int i;

	i = 0;
	while(i < argc){
		puts(*argv++);
		i++;
	}
}

void point_str(char *str, int length){
	int i;

	i = 0;
	while(i < length){
		putchar(*str++);
		i++;
	}
	putchar('\n');
}

void find_char(){
	char *str;
	char *find;

	str = "allocate N=5 node_list=node[001-005],node008 flag=optional timeout=10";
	find = strrchr(str, '=');
	puts(++find);
	putchar(*find);
	putchar('\n');
}

int main(){
	puts("Hello");
	return 0;
}
