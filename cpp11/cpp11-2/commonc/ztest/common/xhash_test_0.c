#include <stdio.h>
#include <stdlib.h>

#include "src/common/xhash.h"
#include "src/common/xmalloc.h"

/*****************************************************************************
 * DEFINITIONS
 *****************************************************************************/

typedef struct {
	char id[255];
	uint32_t idn;
	char name[256];
	int  age;
} person_t;

/*
 * generate unique identifier from a stored item by returning a string.
 *
 * typedef const char* (*xhash_idfunc_t)(void* item);
 */
const char* identify_func(void* voiditem)
{
	person_t *item = (person_t*)voiditem;
	if (!item->id[0])
		snprintf(item->id, 255, "%lu", (unsigned long)item->idn);
	return item->id;
}

void add_age_callback(void *voiditem, void *arg)
{
	person_t *item = (person_t*)voiditem;
	int *add_age = (int *)arg;
	item->age += *add_age;
}

/**
 * ****************************************************
 * Initialize the hash table; Must be freed with xhash_free.
 * xhash_t *xhash_init(xhash_idfunc_t idfunc,
		    xhash_hashfunc_t hashfunc, // Currently: should be NULL
		    uint32_t table_size);      // Currently: unused
 * ****************************************************
 * Add an item to the hash table
 *
 * void* xhash_add(xhash_t* table, void* item);
 * ****************************************************
 * the number of items stored in the hash table
 *
 * uint32_t xhash_count(xhash_t* table);
 * ****************************************************
 * returns an item from a key searching through the hash table. NULL if not found.
 *
 * void* xhash_get(xhash_t* table, const char* key);
 *
 * ****************************************************
 * Remove an item associated with key from the hash table item is if found,
 * but do not free the item memory itself (the user is responsible for
 * managing item's memory).
 *
 * void xhash_delete(xhash_t* table, const char* key);
 * ****************************************************
 * apply callback to each item contained in the hash table
 *
 * void xhash_walk(xhash_t* table,
 * 			void (*callback)(void* item, void* arg),
 * 			void* arg);
 * ****************************************************
 * frees the hash table, but does not free its stored items,
 * you can use xhash_walk to perform a free operation on all items if wanted.
 *
 * void xhash_free(xhash_t* table);
 * ****************************************************
 */
static void init_test(void)
{
	int i, count;
	xhash_t	*my_ht = NULL;

	char *key  = "3";
	person_t *person_ptr = NULL;

	int arg = 1;  /* add_age */

	person_t person_array[5];
	uint32_t person_sum = sizeof(person_array)/sizeof(person_array[0]);
	/********************************************************************************/
	/* init: currently hashfunc is NULL, table_size is 0 */
	my_ht = xhash_init(identify_func, NULL, 0);
	if (!my_ht)
		return; /* fatal error, will be detected by test cases */

	/********************************************************************************/
	/* setup the person_array, add each element to my_ht */
	for (i = 0; i < person_sum; ++i) {
		person_array[i].id[0] = 0;
		person_array[i].idn = i;
		person_array[i].age = i;
		snprintf(person_array[i].name, 256, "name_%d", i);

		/* add person_array[i] to my_ht */
		/* 'person_array + i' equals to  &person_array[i] */
		if (!xhash_add(my_ht, person_array + i))
			return;
	}

	/* only print the person_array, it is irrelated with hashtable */
	puts("after add each element of above person_array to my_ht, we try to print the array: ");
	for (i = 0; i < person_sum; ++i) {
		printf("id = %s, idn = %lu, name = %s, age = %d\n",
				person_array[i].id,
				person_array[i].idn,
				person_array[i].name,
				person_array[i].age
				);
	}

	/********************************************************************************/
	/* get the count of elements now in my_ht  */
	count = xhash_count(my_ht);
	printf("count  = %d elements are added in my_ht\n", count);

	/********************************************************************************/
	/* get the element by key */
	person_ptr = (person_t *)xhash_get(my_ht, key);
	if(NULL == person_ptr)
		puts("no such person in my_ht");
	else
		printf("the person with key is : id=%s, idn=%lu, name=%s, age=%d\n",
				person_ptr->id, person_ptr->idn, person_ptr->name, person_ptr->age);

	/********************************************************************************/
	/* we will delete the element with key from my_ht but not from person_array */
	xhash_delete(my_ht, key);
	/* to examine the delete whether successful or not, we try to get it */
	person_ptr = (person_t *)xhash_get(my_ht, key);
	if(NULL == person_ptr)
		puts("no such person in my_ht");
	else
		printf("the person with key is : id=%s, idn=%lu, name=%s, age=%d\n",
				person_ptr->id, person_ptr->idn, person_ptr->name, person_ptr->age);
	/* to examine the delete operation just from my_ht but not person_array, we print the person_array again */
	puts("just delete it from my_ht, not from person_array, you see : ");
	for (i = 0; i < person_sum; ++i) {
		printf("id = %s, idn = %lu, name = %s, age = %d\n",
				person_array[i].id,
				person_array[i].idn,
				person_array[i].name,
				person_array[i].age
				);
	}
	/********************************************************************************/
	xhash_walk(my_ht, add_age_callback, &arg);
	puts("after walk through my_ht, +1 to each age, then print the person_array: ");
	for (i = 0; i < person_sum; ++i) {
		printf("id = %s, idn = %lu, name = %s, age = %d\n",
				person_array[i].id,
				person_array[i].idn,
				person_array[i].name,
				person_array[i].age
				);
	}

	puts("Note: currently, there are 4 elements in my_ht, and 5 elements in person_array, when *add_age_callback*, it only changes the value of element in my_ht");
	/********************************************************************************/
	xhash_free(my_ht);
}

int main()
{
	init_test();
	return 0;
}

