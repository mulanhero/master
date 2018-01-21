#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *str;
	asprintf(&str, "strlen(\"hello, world!\") = %d", strlen("hello, world!"));
	puts(str);
	if(str){
		printf("I'm free\n");
		free(str);
	}
	return 0;
}
