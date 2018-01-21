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
 * int (*ListCmpF) (void *x, void *y);
 */
int list_compare_f (void *x, void *y)
{
	stu_t *x_t = (stu_t *)x;
	stu_t *y_t = (stu_t *)y;

	return x_t->id - y_t->id;
}

/*
 * 	******************************************************
 *  Traverses list [l] and removes all items in list
 *  If a deletion function was specified when the list was
 *  created, it will be called to deallocate each item being removed.
 *  Returns a count of the number of items removed from the list.
 *
 *  int list_flush (List l);
 *  ******************************************************
 *  Sorts list [l] into ascending order according to the function [f].
 *  Note: Sorting a list resets all iterators associated with the list.
 *  Note: The sort algorithm is stable.
 *
 *  void list_sort (List l, ListCmpF f);
 *  ******************************************************
 */

void list_sort_flush_test()
{
	int i, count;
	char buf[32];
	List target_list = NULL;
	stu_t *node = NULL;
	ListIterator it = NULL;

	/* create target_list and append its elements */
	target_list = list_create(_list_delete_node_f);

	node = xmalloc(sizeof(stu_t));
	node->id = 50;
	node->age = 50;
	sprintf(buf, "stu_%d", 50);
	node->name = xstrdup(buf);
	list_append (target_list, node);

	node = xmalloc(sizeof(stu_t));
	node->id = 100;
	node->age = 100;
	sprintf(buf, "stu_%d", 100);
	node->name = xstrdup(buf);
	list_append (target_list, node);

	node = xmalloc(sizeof(stu_t));
	node->id = 1;
	node->age = 1;
	sprintf(buf, "stu_%d", 1);
	node->name = xstrdup(buf);
	list_append (target_list, node);

	list_sort(target_list, list_compare_f);

	/* create iterator! */
	it = list_iterator_create (target_list);
	/* list_next until NULL */
	while ( NULL != (node = (stu_t*)list_next(it)) ) {
		printf("id = %ld, name = %s, age = %f\n", node->id, node->name, node->age);
	}
	list_iterator_destroy(it);

	puts("before flush.....");
	count = list_flush (target_list);
	printf("count = %d elements has been flushed from the list.\n", count);
	puts("after flush.....");

	list_destroy (target_list);
}

int main()
{
	list_sort_flush_test();
	return 0;
}
