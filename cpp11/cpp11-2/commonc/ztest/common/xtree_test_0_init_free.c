#include <stdio.h>
#include <stdlib.h>

#include "src/common/xtree.h"
#include "src/common/xmalloc.h"

typedef struct {
	unsigned long id;
	char *name;
	int  age;
} person_t;

/**
 * typedef void (*xtree_free_data_function_t)(void* data);
 */
void xtree_free_node_func(void* voiddata)
{
	person_t *person_ptr = (person_t *)voiddata;

	printf("free person_ptr->id = %lu\n", person_ptr->id);

	if (person_ptr) {
		xfree(person_ptr->name);
		xfree(person_ptr);
	}
}


/**
 *********************************************************
 *  void xtree_init(xtree_t* tree, xtree_free_data_function_t freefunc);
 *********************************************************
 *  uint32_t xtree_get_count(xtree_t* tree);
 *********************************************************
 *	The tree itself is freed but the `xtree_t` structure is not free (since it
 *	can be stored on the stack).
 *
 *  void xtree_free(xtree_t* tree);
 *********************************************************
 * uint32_t xtree_depth(xtree_t* tree);
 *********************************************************
 */
void init_tree_test()
{
	xtree_t *my_tree = (xtree_t *)xmalloc(sizeof(xtree_t));
	uint32_t count = 0;
	uint32_t depth = 0;
	xtree_node_t *root_node = NULL;
	xtree_node_t *node = NULL;
	person_t *person = NULL;
	char buf[256];


	/* init my_tree with free element function */
	xtree_init(my_tree, xtree_free_node_func);

	/* get count */
	count = xtree_get_count(my_tree);
	printf("count = %lu, currently, the tree should be empty, so count = 0 is right.\n", count);

	root_node = (xtree_node_t *)xmalloc(sizeof(xtree_node_t));
	person = (person_t *)xmalloc(sizeof(person_t));
	person->id = 1;
	person->age = 1;
	snprintf(buf, 256, "name_%d", 1);
	person->name = xstrdup(buf);
	root_node->data = person;
	root_node->parent = NULL;
	my_tree->root = root_node;
	my_tree->count++;
	my_tree->depth++;

	/* get count */
	count = xtree_get_count(my_tree);
	printf("count = %lu, currently, the tree should be empty, so count = 1 is right.\n", count);

	/* get depth */
	depth = xtree_depth(my_tree);
	printf("depth = %d\n", depth);

	/* to free element */
	xtree_free(my_tree);
	/* to free my_tree itself memory */
	xfree(my_tree);
}

int main()
{
	init_tree_test();
	return 0;
}
