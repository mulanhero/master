#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person{
	char *name;
	int age;
};

typedef struct person person_t;

void array_name()
{
	person_t array[10];
	int i;

	for(i = 0; i < 10; i++){
		asprintf(&array[i].name, "name-%d", i);
		array[i].age = i;
	}

	for(i = 0; i < 10; i++)
		printf("array[%d].name = %s, array[%d].age = %d\n",
				i, array[i].name, i, array[i].age);

	for(i = 0; i < 10; i++)
		printf("array[%d].name = %s, array[%d].age = %d\n",
						i, (*(array+i)).name, i, (*(array+i)).age);

	for(i = 0; i < 10; i++)
		printf("array[%d].name = %s, array[%d].age = %d\n",
						i, (array+i)->name, i, (array+i)->age);
}

void point_to_d1_array()
{
	person_t array[10];
	person_t *p_to_array;
	int i;

	p_to_array = &array[0];
	for(i = 0; i < 10; i++){
		asprintf(&p_to_array->name, "NAME-%d", i);
		p_to_array->age = i;
		p_to_array++;
	}

	p_to_array = array;
	for(i = 0; i < 10; i++)
		printf("array[%d].name = %s, array[%d].age = %d\n",
						i, (p_to_array+i)->name, i, (p_to_array+i)->age);
}

void point_to_d2_array()
{
	person_t array[5][30];
	person_t (*p_to_array)[30];
	int i, j;
	char *age_str;

	p_to_array = array[0];
//	p_to_array = array;

	for(i = 0; i < 5; i++){
		for(j = 0; j < 30; j++){
			asprintf(&array[i][j].name, "NAME-%d-%d", i, j);
//			asprintf(&(p_to_array+i*30+j)->name, "NAME-%d-%d", i, j);
			asprintf(&age_str, "%d%d", i, j);
			array[i][j].age = atoi(age_str);
//			((p_to_array+i*30)+j)->age = atoi(age_str);
		}
	}

	for(i = 0; i < 5; i++){
		for(j = 0; j < 30; j++){
//			printf("array[i][j].name = %s, array[i][j].age = %d\n",
//					i, j, ((p_to_array+i*30)+j)->name,
//					i, j, ((p_to_array+i*30)+j)->age);
			printf("array[%d][%d].name = %s, array[%d][%d].age = %d\n",
					i, j, array[i][j].name,
					i, j, array[i][j].age);
		}
	}
}


int main()
{
	puts("================");
	array_name();
	puts("================");
	point_to_d1_array();
	puts("================");
	point_to_d2_array();
	return 0;
}
