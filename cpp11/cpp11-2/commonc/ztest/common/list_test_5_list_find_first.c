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

/*
 *  ******************************************************
 *  Traverses list [l] using [f] to match each item with [key].
 *  Returns a ptr to the first item for which the function [f]
 *    returns non-zero, or NULL if no such item is found.
 *  Note: This function differs from list_find() in that it does not require
 *    a list iterator; it should only be used when all list items are known
 *    to be unique (according to the function [f]).
 *
 *  void * list_find_first (List l, ListFindF f, void *key);
 *  ******************************************************
 */
void list_find_first_test()
{
	int i, count;
	char buf[32];
	List target_list = NULL;
	stu_t *node = NULL;
	ListIterator it = NULL;
	long key = 90005;

	/* create target_list and append its elements */
	target_list = list_create(_list_delete_node_f);
	for (i = 0; i < 10; i++) {
		node = xmalloc(sizeof(stu_t));
		node->id = (90000L+i);
		node->age = i;
		sprintf(buf, "stu_%d", i);
		node->name = xstrdup(buf);
		list_append (target_list, node);
	}

	for (i = 0; i < 10; i++) {
		node = xmalloc(sizeof(stu_t));
		node->id = (90000L+i);
		node->age = i+1;
		sprintf(buf, "stu_%d", i+1);
		node->name = xstrdup(buf);
		list_append (target_list, node);
	}

	/* so there are two elements having the key, but return the first found*/
	node = (stu_t *) list_find_first (target_list, list_find_stu_id_f, &key);
	if (NULL != node)
		printf("id = %ld, name = %s, age = %f\n", node->id, node->name, node->age);

	list_destroy (target_list);
}

int main()
{
	list_find_first_test();
	return 0;
}
