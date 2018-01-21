/*
 * array_point.c
 *
 *  Created on: Dec 16, 2012
 *      Author: caoj7
 */
#include <stdio.h>

/*
 * pointer can move forward
 */
void print_pointer(char **array_ptr)
{
	while(*array_ptr){
		puts(*array_ptr++);
	}
}
/*
 * array's name can not move forward
 */
void print_array(char *array[])
{
	int i;
	for(i = 0; array[i] != NULL; i++)
		puts(array[i]);
}

void pointer_run()
{
	char *str_array[] = {"beijing", "shanghai", "shenzhen", "xian", NULL};
	char **str_array_pt, **remember_pt;

	str_array_pt = str_array;

	remember_pt = str_array_pt; //to remember the original location

	while(*str_array_pt)
		puts(*str_array_pt++); //pointer is gone

	while(*remember_pt)
		puts(*remember_pt++);
}

int main (int argc, char *argv[])
{
	char *str_array[] = {"beijing", "shanghai", "wuhan", "xian", NULL};
	print_pointer(str_array);
	print_array(str_array);
	//========================
	pointer_run();
	return 0;
}

