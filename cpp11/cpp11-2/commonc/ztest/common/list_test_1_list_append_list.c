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
 * int list_append_list (List l, List sub);
 */
void list_append_list_test()
{
	int i, count;
	char buf[32];
	List target_list = NULL;
	List sub_list = NULL;
	stu_t *node = NULL;
	ListIterator it = NULL;

	/* create target_list and append its elements */
	target_list = list_create(NULL);
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

	/* append_list, Note: the target list must have a destroy function of NULL */
	count = list_append_list (target_list, sub_list);
	printf("count = %d nodes from sub_list has been appended to target_list\n", count);

	/* create iterator! */
	it = list_iterator_create (target_list);
	/* list_next until NULL */
	while ( NULL != (node = (stu_t*)list_next(it)) ) {
		printf("id = %ld, name = %s, age = %f\n", node->id, node->name, node->age);
	}
	list_iterator_destroy(it);

	/* list_destroy : destroy the list */
	list_destroy (target_list);

}

int main()
{
	list_append_list_test();
	return 0;
}
