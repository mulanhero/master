/*
 * fn_struct.c
 *
 *  Created on: Jan 23, 2013
 *      Author: caoj7
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

struct fn_struct{
	char* (*add)(char *str1, char *str2);
	bool (*iscontain)(char *str1, char *str2);
};

typedef struct fn_struct fn_struct_t;

static char* ad(char *str1, char *str2){
	char *rt;
	rt = (char*)malloc(strlen(str1) + strlen(str2) +1);
	strcpy(rt, str1);
	rt = strcat(rt, str2);
	return rt;
}

static bool iscnt(char *str1, char *str2){
	if(strstr(str1, str2))
		return true;
	else
		return false;
}

fn_struct_t fn = {
			ad,
			iscnt
};


int main()
{
	char *str1 = "beijing shanghai xian";
	char *str2 = "xian";
	bool flag;

	printf("%s\n", fn.add(str1, str2));

	flag = fn.iscontain(str1, str2);
	if(true == flag)
		printf("%s contain %s = %s\n", str1, str2, "true");
	else
		printf("%s contain %s = %s\n", str1, str2, "false");

	return 0;

}
