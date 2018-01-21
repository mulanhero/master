/*
 * env.c
 *
 *  Created on: Dec 10, 2012
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>

/*
 *  #include <stdlib.h>
       int setenv(const char *name, const char *value, int overwrite);
       int unsetenv(const char *name);

     #include <stdlib.h>
       char *getenv(const char *name);
 */
typedef int bool;
#define true 1
#define false 0

extern char **environ;

void print_all_env(){
	 char **ep = environ;
	 char *p;
	 while ((p = *ep++))
		 printf("%s\n", p);
}

int main()
{
	print_all_env();
	setenv("NAME", "JIMMY", true);
	printf("NAME = %s\n", getenv("NAME"));
	return 0;
}

