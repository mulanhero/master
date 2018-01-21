#include <stdio.h>
#include <stdlib.h>

/*
 * const int ro_i = 123;
 * const int *ro_i_p;
 */
void read_only_variable(void)
{
	const int ro_i = 123;
	/* can not be revised */
	printf("ro_i = %d\n", ro_i);
	/* const variable ro_i can be read only */
//	ro_i = 321;   //error

	/* which means that now cp is an ordinary, modifiable pointer,
	 * but the thing that it points to must not be modified.
	 */
	const int *ro_i_p;
	ro_i_p = &ro_i;
	printf("ro_i = %d, *ro_i_p = %d\n", ro_i, *ro_i_p);

	/* const int pointer ro_i_p can point to others,
	 * but the position to which it points can not be revised.
	 */
	int i = 456;
	ro_i_p = &i;
	printf("i = %d, *ro_i_p = %d\n", i, *ro_i_p);

//	*ro_i_p = 789; //error

	i = 789;
	printf("i = %d, *ro_i_p = %d\n", i, *ro_i_p);
}


void un_modified_pointer(void)
{
	char ch1 = 'A', ch2 = 'a';
	/*
	 * The const means that cp is not to be modified,
	 * although whatever it points to can be—the pointer
	 * is constant, not the thing that it points to.
	 */
	char * const pt = &ch1;
	printf("ch1 = %c, *pt = %c\n", ch1, *pt);
	/* can not points to others */
//	pt = &ch2;   //error
}


int main()
{
	read_only_variable();
	un_modified_pointer();
	return 0;
}
