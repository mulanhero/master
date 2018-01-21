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
 *  ******************************************************
 *  Inserts data [x] at the end of list [l].
 *  Returns the data's ptr, or lsd_nomem_error() if insertion failed.
 *
 *  void * list_append (List l, void *x);
 *  ******************************************************
 *	Inserts data [x] at the beginning of list [l].
 *	Returns the data's ptr, or lsd_nomem_error() if insertion failed.
 *
 *	void * list_prepend (List l, void *x);
 *  ******************************************************
 */
void list_append_prepend()
{
	int i, count;
	char buf[32];
	List target_list = NULL;
	stu_t *node = NULL;
	ListIterator it = NULL;

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

	/* prepend other 10 elements */
	for (i = 0; i < 10; i++) {
		node = xmalloc(sizeof(stu_t));
		node->id = (100000L+i);
		node->age = 100+i;
		sprintf(buf, "stu_sub_%d", 100+i);
		node->name = xstrdup(buf);
		list_prepend (target_list, node);
	}

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
	list_append_prepend();
	return 0;
}
