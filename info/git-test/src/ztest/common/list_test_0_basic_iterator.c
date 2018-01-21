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

List stu_list = NULL;
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


/********************    ListIterator   *****************************/
/**
 * ListIterator list_iterator_create (List l);
 * void * list_next (ListIterator i);
 * void list_iterator_reset (ListIterator i);
 * void *list_insert (ListIterator i, void *x);
 * void * list_find (ListIterator i, ListFindF f, void *key);
 * void list_iterator_destroy (ListIterator i)
 * void * list_remove (ListIterator i);
 * int list_delete_item (ListIterator i);
 */
void it_test_1()
{
	ListIterator it = NULL;
	stu_t *node = NULL;
	long key = 90005L;
	void *pos = NULL;
	int count = 0;

	/* create iterator! */
	it = list_iterator_create (stu_list);
	/* list_next until NULL */
	while ( NULL != (node = (stu_t*)list_next(it)) ) {
		printf("id = %ld, name = %s, age = %f\n", node->id, node->name, node->age);
	}

	/********** insert ******************/
	/* reset it to the start of list */
	list_iterator_reset(it);
	while ( NULL != (node = (stu_t*)list_next(it)) ) {
		if (5 == node->age){
			node = xmalloc(sizeof(stu_t));
			node->id = 999999L;
			node->age = 5.5;
			node->name = xstrdup("name_5.5");
			/* list_insert: insert a new node */
			list_insert (it, node);
			break;
		}
	}

	/*******  traverse: the list via list_next(it) **********/
	/* reset it to the start of list */
	list_iterator_reset(it);
	/* after insert, list_next until NULL */
	puts("=========after insert:");
	while ( NULL != (node = (stu_t*)list_next(it)) ) {
		printf("id = %ld, name = %s, age = %f\n", node->id, node->name, node->age);
	}

	/************   find    ******************/
	/* reset it to the start of list */
	list_iterator_reset(it);
	/* list_find: traverse the list using *it*, to find the node with the '*key' */
	if (NULL != (pos = list_find(it, list_find_stu_id_f, &key))) {
		printf("found! id = %ld, name = %s, age = %f\n", ((stu_t *)pos)->id, ((stu_t *)pos)->name, ((stu_t *)pos)->age);
	} else {
		puts("not found");
	}

	/************   remove    ******************/
	/* remove the node to which 'it' currently points, does not free the node */
	pos = list_remove (it);
	printf("removed! id = %ld, name = %s, age = %f\n", ((stu_t *)pos)->id, ((stu_t *)pos)->name, ((stu_t *)pos)->age);
	/* Note: free the removed node */
	xfree(((stu_t *)pos)->name);
	xfree(pos);

	/* reset it to the start of list */
	list_iterator_reset(it);
	/* after remove, list_next until NULL */
	puts("=========after remove, list is:");
	while ( NULL != (node = (stu_t*)list_next(it)) ) {
		printf("id = %ld, name = %s, age = %f\n", node->id, node->name, node->age);
	}


	/************   find  and delete   ******************/
	/* reset it to the start of list */
	list_iterator_reset(it);
	/* list_find: traverse the list using *it*, to find the node with the '*key' */
	key = 999999L;
	if (NULL != (pos = list_find(it, list_find_stu_id_f, &key))) {
		printf("found! id = %ld, name = %s, age = %f\n", ((stu_t *)pos)->id, ((stu_t *)pos)->name, ((stu_t *)pos)->age);
	} else {
		puts("not found");
	}

	/* delete item, automatically free the item's memory via
	 * the default delete func specified when
	 * list_create(_list_delete_node_f)
	 */
	count = list_delete_item (it);
	if (count == 1)
		puts("deleting successful");
	else
		puts("deleting failed");
	/* reset it to the start of list */
	list_iterator_reset(it);
	/* after deleting, list_next until NULL */
	puts("=========after deleting, list is:");
	while ( NULL != (node = (stu_t*)list_next(it)) ) {
		printf("id = %ld, name = %s, age = %f\n", node->id, node->name, node->age);
	}

	/* Note: remember to destroy iterator */
	list_iterator_destroy(it);
}


/**
 * *******************************
 * * General-Purpose Functions  *
 * *******************************
 * List list_create (ListDelF f)
 * void list_destroy (List l);
 * int list_is_empty (List l);
 * int list_count (List l);
 * *****************************
 * void *list_append (List l, void *x)
 * void list_install_fork_handlers (void);
 */

int main()
{
	stu_t *node = NULL;
	int i;
	char buf[32];
	int sum = 0;
	int count = 0;

	/* create */
	stu_list = list_create(_list_delete_node_f);
	list_install_fork_handlers();

	/* list_is_empty : if empty ? */
	if (1 == list_is_empty(stu_list))
		puts("list is empty");
	else
		puts("list is non-empty");

	/* append  */
	for (i = 0; i < 10; i++) {
		node = xmalloc(sizeof(stu_t));
		node->id = (90000L+i);
		node->age = i;
		sprintf(buf, "stu_%d", i);
		node->name = xstrdup(buf);
		list_append (stu_list, node);
	}

	/* list_count: the count of node in list */
	sum = list_count (stu_list);
	printf("count = %d\n", sum);

	/* ListIterator operations!! */
	it_test_1();

	/* list_destroy : destroy the list
	 * automatically call the default routine to free memory for each node
	 */
	list_destroy (stu_list);
	return 0;
}
