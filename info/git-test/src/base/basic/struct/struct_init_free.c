#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_VAL 0xfffe

typedef struct {
	int age;
	char *name;
	char *address;
}person_t;


void init_person(person_t *pp)
{
	memset(pp, 0, sizeof(person_t));
	pp->age = NO_VAL;
}

void free_person(person_t *pp)
{
	if (pp){
		free(pp->name);
		free(pp->address);
		free(pp);
	}
}

void test1()
{
	person_t he;
	init_person(&he);

	printf("age = %d, name = %s, address = %s\n",
		he.age, he.name, he.address);

	he.age = 100;
	he.name = strdup("xiaoming");
	he.address = strdup("shanghai");

	printf("age = %d, name = %s, address = %s\n",
		he.age, he.name, he.address);

	free(he.name);
	free(he.address);

	printf("age = %d, name = %s, address = %s\n",
		he.age, he.name, he.address);
}

void test2()
{
	person_t *he;
	he = (person_t *)malloc(sizeof(person_t));

	init_person(he);
	printf("age = %d, name = %s, address = %s\n",
		he->age, he->name, he->address);

	he->age = 200;
	he->name = strdup("he2");
	he->address = strdup("xian");

	printf("age = %d, name = %s, address = %s\n",
		he->age, he->name, he->address);

	free_person(he);

}

int main()
{
#if 0
	test1();
#endif
	test2();
	return 0;
}
