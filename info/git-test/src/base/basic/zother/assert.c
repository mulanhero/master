/* define NDEBUG before #include<assert.h> will make 'assert' disabled */
//#define NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void func(void)
{
	char ch;
	puts("please input a char:");
	ch = getchar();
	assert(ch != EOF);
	putchar(ch);
}

int main()
{
	func();
	return 0;
}
