#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *str;
	str = strdup("beijing");
	puts(str);
	free(str);
	return 0;
}
