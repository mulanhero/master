#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int age;
	char name[20];
}boy_t;

typedef struct {
	int age;
	char *name;
}girl_t;

int main()
{
	boy_t jimmy;
	jimmy.age = 12;
	strcpy(jimmy.name, "jimmy cao");
	printf("name = %s, age = %d\n", jimmy.name, jimmy.age);

	girl_t rose;
	rose.age = 10;
	rose.name = (char *)malloc(sizeof("rose li")+1);
	strcpy(rose.name, "rose li");
	printf("name = %s, age = %d\n", rose.name, rose.age);
	/*!!!*/
	free(rose.name);

	girl_t lily;
	lily.age = 11;
	lily.name = strdup("lily wang");
	printf("name = %s, age = %d\n", lily.name, lily.age);
	/*!!!*/
	free(lily.name);

	return 0;
}
