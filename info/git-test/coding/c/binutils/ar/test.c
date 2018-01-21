#include <stdio.h>
#include "foobar.h"
int main()
{
	int i = 5;
	int j = 10;

	foo(&i);
	foo(&j);

	printf("i = %d\n", i);
	printf("j = %d\n", j);
	return 0;
}
