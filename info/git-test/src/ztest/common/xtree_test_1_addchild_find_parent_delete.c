#include <stdio.h>
#include <stdlib.h>

#include "src/common/xtree.h"
#include "src/common/xmalloc.h"

typedef struct {
	uint32_t id;
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
 * typedef uint8_t (*xtree_find_compare_t)(const void* node_data,
					const void* arg);
 */
uint8_t find_compare_func(const void* node_data, const void* arg)
{
	person_t *person = (person_t *)node_data;
	uint32_t *id =  (uint32_t *)arg;

	if(*id == person->id)
		return 0;
	else
		return 1;
}

/**
 *********************************************************
 * xtree_node_t* xtree_add_child(xtree_t* tree,
			      xtree_node_t* parent,
			      void* data,
			      uint8_t flags);
 *********************************************************
 * xtree_node_t* xtree_find(xtree_t* tree,
			 xtree_find_compare_t compare,
			 const void* arg);
 *********************************************************
 * xtree_node_t* xtree_get_parent(xtree_t* tree, xtree_node_t* node);
 *********************************************************
 *	uint32_t xtree_node_depth(const xtree_node_t* node);
 *********************************************************
 * xtree_node_t* xtree_delete(xtree_t* tree, xtree_node_t* node);
 *********************************************************
 */

/* here we construct a tree in the following form :
 *       1
 *    / / \  \
 *    6 2  3  5
 *     / \
 *     7  4
 * numbers are chronological adding order.
 */
void addchild_walk_test()
{
	xtree_t *my_tree = (xtree_t *)xmalloc(sizeof(xtree_t));
	person_t *person = NULL;
	person_t *direct_parent_person = NULL;
	person_t *parent_of_delete_person = NULL;
	char buf[256];
	xtree_node_t* node = NULL;
	xtree_node_t* direct_parent_node = NULL;
	xtree_node_t* parent_of_delete_node = NULL;
	uint32_t arg = 0;
	int i;

	/* init my_tree with free element function */
	xtree_init(my_tree, xtree_free_node_func);

	for (i = 1; i < 8; i++) {
		person = (person_t *)xmalloc(sizeof(person_t));
		person->id = i;
		person->age = i;
		snprintf(buf, 256, "name_%d", i);
		person->name = xstrdup(buf);

		if (1 == i)
			xtree_add_child(my_tree, NULL, person, XTREE_APPEND);
		else if (2 == i)
			xtree_add_child(my_tree, my_tree->root, person, XTREE_APPEND);
		else if (3 == i)
			xtree_add_child(my_tree, my_tree->root, person, XTREE_APPEND);
		else if (4 == i) /* my_tree->root is 1, then 1's ->start is 2 */
			xtree_add_child(my_tree, my_tree->root->start, person, XTREE_APPEND);
		else if (5 == i)
			xtree_add_child(my_tree, my_tree->root, person, XTREE_APPEND);
		else if (6 == i)
			xtree_add_child(my_tree, my_tree->root, person, XTREE_PREPEND);
		else if (7 == i) /* my_tree->root is 1, then 1's ->start is 2 */ /* XTREE_PREPEND */
			xtree_add_child(my_tree, my_tree->root->start->next, person, XTREE_PREPEND);
	}

	arg = 4;
	node = xtree_find(my_tree, find_compare_func, &arg);

	if (NULL != node) {
		person = (person_t *) node->data;
		puts("xtree_find success!, my info: ");
		printf("person->id = %lu\n", person->id);
		printf("person->age = %lu\n", person->age);
		printf("person->name = %s\n", person->name);
		/* print person's depth */
		printf("person\'s depth = %lu\n", xtree_node_depth(node));

		puts("my parent\'s info: ");
		direct_parent_node = xtree_get_parent(my_tree, node);
		direct_parent_person = (person_t *) direct_parent_node->data;
		printf("direct_parent_person->id = %lu\n", direct_parent_person->id);
		printf("direct_parent_person->age = %lu\n", direct_parent_person->age);
		printf("direct_parent_person->name = %s\n", direct_parent_person->name);
		/* print parent's depth */
		printf("parent's depth = %lu\n", xtree_node_depth(direct_parent_person));

		puts("try to delete the parent node (2):");
		parent_of_delete_node = xtree_delete(my_tree, direct_parent_node);
		parent_of_delete_person = (person_t *)parent_of_delete_node->data;
		printf("parent_of_delete_person->id = %lu\n", parent_of_delete_person->id);
		printf("parent_of_delete_person->age = %lu\n", parent_of_delete_person->age);
		printf("parent_of_delete_person->name = %s\n", parent_of_delete_person->name);
	}

	puts("at last, free all nodes in the tree:");
	/* to free element */
	xtree_free(my_tree);
	/* to free my_tree itself memory */
	xfree(my_tree);
}

int main()
{
	addchild_walk_test();
	return 0;
}
