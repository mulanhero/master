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
 *  Enqueues data [x] at the tail of queue [l].
 *  Returns the data's ptr, or lsd_nomem_error() if insertion failed.
 *
 *  void * list_enqueue (List l, void *x);
 *  -----------------------------------
 *  Dequeues the data item at the head of the queue [l].
 *  Returns the data's ptr, or NULL if the queue is empty.
 *
 *  void * list_dequeue (List l);
 */
void list_enqueue_dequeue()
{
	int i, j;
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
		/* list_enqueue */
		list_enqueue (target_list, (void *)node);
	}

	/* list_dequeue, and free the node using _list_delete_node_f */
	while (NULL != (node = (stu_t*)list_dequeue(target_list))) {
		printf("id = %ld, age = %f, name = %s\n", node->id, node->age, node->name);
		_list_delete_node_f(node);
	}

	printf("after list_dequeue, the count = %d\n", list_count(target_list));
	/* list_destroy : destroy the list */
	list_destroy (target_list);
}


int main()
{
	list_enqueue_dequeue();
	return 0;
}
