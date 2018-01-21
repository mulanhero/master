#include <stdio.h>
#include <stdlib.h>

/*
 * #include <stdlib.h>
 * int rand(void);
 * int rand_r(unsigned int *seedp);
 * void srand(unsigned int seed);
 */

int main()
{
	int rd;

	srand(time(NULL));  //seed
	rd = rand() % 10;
	printf("rd = %d\n", rd);
	return 0;
}
