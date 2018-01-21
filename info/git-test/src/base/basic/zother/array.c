#include <stdio.h>
#include <stdlib.h>

int main()
{	
	int *array_ptr = NULL;
	int array[] = {2, 34, 56};

	array_ptr = array;
	printf("sizeof(array)/sizeof(int) = %lu\n", sizeof(array)/sizeof(int));
	printf("sizeof(array_ptr) = %lu\n", sizeof(array_ptr));
	return 0;
}
