#include <stdio.h>
#include <stdlib.h>

typedef struct proc_exitcode {
	int pid;
	int exitcode;
} proc_exitcode_t;

void print(proc_exitcode_t *array, int array_len) {
	int i;
	for (i = 0; i < array_len; i++) {
		printf("array[%d].pid = %d, array[%d].exitcode = %d\n", i, array[i].pid, i, array[i].exitcode);
	}
}

void print2(int *array, int array_len)
{
	int i;
	for (i = 0; i < array_len; i++) {
		printf("array[%d] = %d\n", i, array[i]);
	}
}

int main()
{
 	proc_exitcode_t array[] = {1, 1};
	print(array,1);

	proc_exitcode_t *p = malloc(sizeof(proc_exitcode_t));
	p->pid = 9; p->exitcode = 9;

	print(p, 1);
	free(p);

	int iarray[] = {1};
	print2(iarray, 1);
	int pid = 4;
	int my[1] = {pid};
	print2(my, 1);

	return 0;

}
