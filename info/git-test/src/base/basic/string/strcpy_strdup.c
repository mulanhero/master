/*
 * strcpy_strdup.c
 *
 *  Created on: Dec 18, 2012
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

int main(){
	char copy[SIZE];
	strcpy(copy, "Hello World for copy");
	puts(copy);

	char *dup;
	dup = strdup("Hello World for dup");
	puts(dup);
	/* remember to free, or will memory leak*/
	free(dup);

	char *as;
	asprintf(&as, "%s", "Hello World for as");
	puts(as);
	/* remember to free, or will memory leak*/
	free(as);
	return 0;
}
