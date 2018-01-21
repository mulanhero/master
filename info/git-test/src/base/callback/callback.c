#include <stdio.h>
#include <stdlib.h>

void add(int *a)
{
	printf("result = %d\n", *a + 1);
}

void register_cb(int flag, void* (*func_ptr)(void *), void *p) 
{
	if (flag != 0){
		func_ptr(p);
	} else{
		puts("null");
	}
}

int main()
{
	int p = 10;
	register_cb(1, add, (void*)&p);
	return 0;

}
