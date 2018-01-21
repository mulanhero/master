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
 * 	----------------------------------------
 *  Pushes data [x] onto the top of stack [l].
 *  Returns the data's ptr, or lsd_nomem_error() if insertion failed.
 *
 *  void * list_push (List l, void *x);
 * 	----------------------------------------
 *  Pops the data item at the top of the stack [l].
 *  Returns the data's ptr, or NULL if the stack is empty.
 *
 *  void * list_pop (List l);
 *  ----------------------------------------
 */
void simple_push_pop()
{
	int i, j;
	char buf[32];
	List target_list = NULL;
	stu_t *node = NULL;

	/* create target_list and append its elements */
	target_list = list_create(_list_delete_node_f);

	for (i = 0; i < 10; i++) {
		node = xmalloc(sizeof(stu_t));
		node->id = (90000L+i);
		node->age = i;
		sprintf(buf, "stu_%d", i);
		node->name = xstrdup(buf);
		/* list_enqueue */
		list_push (target_list, (void *)node);
	}

	/* list_dequeue, and free the node using _list_delete_node_f */
	while (NULL != (node = (stu_t*)list_pop(target_list))) {
		printf("id = %ld, age = %f, name = %s\n", node->id, node->age, node->name);
		_list_delete_node_f(node);
	}

	printf("after list_pop, the count = %d\n", list_count(target_list));
	/* list_destroy : destroy the list */
	list_destroy (target_list);
}

/*
 *  ----------------------------------------
 *  Pops the top priority data item from the stack [l].
 *  Returns the data's ptr, or NULL if the stack is empty.
 *
 *  void * list_pop_top (List l, ListCmpF f);
 *  ----------------------------------------
 *  Pops the lowest priority data item from the stack [l].
 *  Returns the data's ptr, or NULL if the stack is empty.
 *
 *  void * list_pop_bottom (List l, ListCmpF f);
 *	----------------------------------------
 *  Peeks at the data item at the top of the stack (or head of the queue) [l].
 *  Returns the data's ptr, or NULL if the stack (or queue) is empty.
 *  Note: The item is not removed from the list.
 *
 *  void * list_peek (List l);
 *  ----------------------------------------
 */
void peek_pop_top_bottom()
{
	char buf[32];
	List target_list = NULL;
	stu_t *node = NULL;

	/* create target_list and append its elements */
	target_list = list_create(_list_delete_node_f);

	node = xmalloc(sizeof(stu_t));
	node->id = 50L;
	node->age = 50;
	strcpy(buf, "name_50L");
	node->name = xstrdup(buf);
	list_push (target_list, (void *)node);

	node = xmalloc(sizeof(stu_t));
	node->id = 1L;
	node->age = 1;
	strcpy(buf, "name_1L");
	node->name = xstrdup(buf);
	list_push (target_list, (void *)node);


	node = xmalloc(sizeof(stu_t));
	node->id = 100L;
	node->age = 100;
	strcpy(buf, "name_100L");
	node->name = xstrdup(buf);
	list_push (target_list, (void *)node);

	/* peek the head of stack/queue, will not remove it from stack/queue */
	node = (stu_t*)list_peek(target_list);
	if (NULL != node)
		printf("list_peek's id = %ld, age = %f, name = %s\n", node->id, node->age, node->name);
	printf("after list_peek, the count = %d\n", list_count(target_list));

	puts("----------------------");


	/* pop the top priority, and free the node's memory */
	node = (stu_t*)list_pop_top(target_list, list_compare_f);
	if (NULL != node)
		printf("list_pop_top's id = %ld, age = %f, name = %s\n", node->id, node->age, node->name);
	_list_delete_node_f(node); /*free the memory */
	printf("after list_pop_top, the count = %d\n", list_count(target_list));

	puts("----------------------");

	/* pop the bottom priority, and free the node's memory */
	node = (stu_t*)list_pop_bottom(target_list, list_compare_f);
	if (NULL != node)
		printf("list_pop_bottom's id = %ld, age = %f, name = %s\n", node->id, node->age, node->name);
	_list_delete_node_f(node); /*free the memory */
	printf("after list_pop_bottom, the count = %d\n", list_count(target_list));

	puts("----------------------");

	/* list_destroy : destroy the list */
	list_destroy (target_list);
}


int main()
{
#if 0
	simple_push_pop();
#endif
	peek_pop_top_bottom();
	return 0;
}
