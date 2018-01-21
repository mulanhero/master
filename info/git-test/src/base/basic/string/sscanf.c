#include <stdio.h>
#include <stdlib.h>

int main()
{
	char str[20];
	int sum;

	char *line = "value = 10";
	sscanf(line, "%s = %d", str, &sum);

	printf("str = %s\n", str);
	printf("sum = %d\n", sum);
	return 0;
}
