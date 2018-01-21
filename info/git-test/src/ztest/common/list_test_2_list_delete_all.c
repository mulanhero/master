#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

#include "src/common/list.h"
#include "src/common/xmalloc.h"

typedef struct {
	long id;
	float age;
	char *name;
} stu_t;


static pthread_mutex_t state_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
 * List list_create (ListDelF f);
 */
void _list_delete_node_f(void *item)
{
	stu_t *s_ptr = (stu_t *) item;
	if (NULL != s_ptr->name)
		xfree(s_ptr->name);
	xfree(s_ptr);
	puts("************** default free node");
}

/**
 * 	typedef int (*ListFindF) (void *x, void *key);
 */
int list_find_stu_id_f(void *x, void *key)
{
	stu_t *pt = NULL;
	long *id = NULL;

	pt = (stu_t *)x;
	id = (long*)key;

	if (*id == pt->id)
		return 1;
	else
		return 0;
}

/**
 * int list_delete_all (List l, ListFindF f, void *key);
 */
void list_delete_all_test()
{
	int i, j;
	char buf[32];
	List target_list = NULL;
	stu_t *node = NULL;
	ListIterator it = NULL;
	long key = 90005;   /* to remove all node with id == key */
	int delete_count = 0;

	/* create target_list and append its elements */
	target_list = list_create(_list_delete_node_f);

	for (j = 0; j < 2; j++){
		for (i = 0; i < 10; i++) {
			node = xmalloc(sizeof(stu_t));
			node->id = (90000L+i);
			node->age = i+j;
			sprintf(buf, "stu_%d_%d", j, i);
			node->name = xstrdup(buf);
			list_append (target_list, node);
		}
	}

	/* create iterator! */
	it = list_iterator_create (target_list);
	/* list_next until NULL */
	while ( NULL != (node = (stu_t*)list_next(it)) ) {
		printf("id = %ld, name = %s, age = %f\n", node->id, node->name, node->age);
	}

	/*-------------------------*/
	delete_count = list_delete_all (target_list, list_find_stu_id_f, &key);
	printf("delete_count = %d\n", delete_count); /* should be: 2*/
	/*-------------------------*/
	puts("after list_delete_all :");
	list_iterator_reset(it);
	while ( NULL != (node = (stu_t*)list_next(it)) ) {
		printf("id = %ld, name = %s, age = %f\n", node->id, node->name, node->age);
	}

	list_iterator_destroy(it);
	/* list_destroy : destroy the list */
	list_destroy (target_list);

}


int main()
{
	list_delete_all_test();
	return 0;
}
