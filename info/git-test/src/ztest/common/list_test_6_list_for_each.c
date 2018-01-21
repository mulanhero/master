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

/*
 *  Function prototype for operating on each item in a list.
 *  Returns less-than-zero on error.
 *
 *  typedef int (*ListForF) (void *x, void *arg);
 */
int list_for_f (void *x, void *arg)
{
	long *arg_tmp = (long*)arg;
	stu_t *node = (stu_t *)x;

	node->id += *arg_tmp;
	return 0;
}

/*
 *  ******************************************************
 *  For each item in list [l], invokes the function [f] with [arg].
 *  Returns a count of the number of items on which [f] was invoked.
 *  If [f] returns <0 for a given item, the iteration is aborted and the
 *    function returns the negative of that item's position in the list.
 *
 *  int list_for_each (List l, ListForF f, void *arg);
 *  ******************************************************
 */
void list_for_each_test()
{
	int i, count;
	char buf[32];
	List target_list = NULL;
	stu_t *node = NULL;
	ListIterator it = NULL;
	long arg = 900000;

	/* create target_list and append its elements */
	target_list = list_create(_list_delete_node_f);
	for (i = 0; i < 10; i++) {
		node = xmalloc(sizeof(stu_t));
		node->id = i;
		node->age = i;
		sprintf(buf, "stu_%d", i);
		node->name = xstrdup(buf);
		list_append (target_list, node);
	}

	count = list_for_each(target_list, list_for_f, &arg);
	printf("count = %d elements has been taken effect with list_for_f", count);
	puts("after each element's id + 900000, then current id:");

	/* create iterator! */
	it = list_iterator_create (target_list);
	/* list_next until NULL */
	while ( NULL != (node = (stu_t*)list_next(it)) ) {
		printf("id = %ld, name = %s, age = %f\n", node->id, node->name, node->age);
	}

	list_iterator_destroy(it);
	list_destroy (target_list);
}

int main()
{
	list_for_each_test();
	return 0;
}
