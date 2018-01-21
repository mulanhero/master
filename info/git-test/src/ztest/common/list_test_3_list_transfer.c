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
 *  Pops off list [sub] and appends data at the end of list [l].
 *  Note: list [l] must have the same destroy function as list [sub].
 *  Note: list [sub] will be returned empty, but not destroyed.
 *  Returns a count of the number of items added to list [l].
 *
 *  int list_transfer (List l, List sub);
 */
void list_transfer_test()
{
	int i, count;
	char buf[32];
	List target_list = NULL;
	List sub_list = NULL;
	stu_t *node = NULL;
	ListIterator it = NULL;

	/* Note1: target_list and sub_list have the same _list_delete_node_f */
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

	/* create sub_list and append its elements */
	sub_list = list_create(_list_delete_node_f);
	for (i = 0; i < 10; i++) {
		node = xmalloc(sizeof(stu_t));
		node->id = (100000L+i);
		node->age = 100+i;
		sprintf(buf, "stu_sub_%d", 100+i);
		node->name = xstrdup(buf);
		list_append (sub_list, node);
	}

	/* *************************************************************\
	 * Note2: the difference between list_transfer and list_append_list:
	 * list_append_list: ListA with list_create(NULL)
	 * list_transfer: 1) listA and ListB has the same DelF in list_create(_list_delete_node_f)
	 * 				  2) after tranfer, sub_list have no element
	 * *************************************************************/

	/* list_transfer */
	count = list_transfer (target_list, sub_list);
	printf("count = %d nodes from sub_list has been transferred to target_list\n", count);

	/* create iterator! */
	it = list_iterator_create (target_list);
	/* list_next until NULL */
	while ( NULL != (node = (stu_t*)list_next(it)) ) {
		printf("id = %ld, name = %s, age = %f\n", node->id, node->name, node->age);
	}
	list_iterator_destroy(it);

	/* list_destroy : destroy the list */
	list_destroy (sub_list);
	puts("the above list_destroy(sub_list) should no element freeing printing, because after tranfer, sub_list have no element");
	list_destroy (target_list);
}

int main()
{
	list_transfer_test();
	return 0;
}
