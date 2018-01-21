/*
 * test.c
 *
 *  Created on: Nov 20, 2012
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_argv_count(char **argv){
	if(argv == NULL)
		return 0;

	int count = 0;
	while(*argv++)
		count++;
	return count;
}
//good
void print_argv(char **argv){
	while(*argv)
		puts(*argv++);
}
/**
 *array name can not ++
 */
//void print1(){
//	char *city_array[] = {"shanghai", "beijing", "tianjin", "xian", "chongqi", NULL};
//	while(*city_array)
//			puts(*city_array++);
//}

int main(int argc, char **argv){
	char *argv_array[] = {"xian", "shanghai", "beijing", "shenzhen", NULL };
	print_argv(argv_array);
	printf("count = %d\n", get_argv_count(argv_array));
	return 0;
}
