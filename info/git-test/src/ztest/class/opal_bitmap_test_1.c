#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "src/class/opal_bitmap.h"

#define SIZE 10

static void construct(opal_bitmap_t *bm)
{
    OBJ_CONSTRUCT(bm, opal_bitmap_t);
}

static void destruct(opal_bitmap_t *bm)
{
    OBJ_DESTRUCT(bm);
}
/**

int opal_bitmap_init (opal_bitmap_t *bm, int size);
int opal_bitmap_set_bit(opal_bitmap_t *bm, int bit);
char * opal_bitmap_get_string(opal_bitmap_t *bitmap);

int opal_bitmap_clear_bit(opal_bitmap_t *bm, int bit);
bool opal_bitmap_is_set_bit(opal_bitmap_t *bm, int bit);

 */
int main()
{
	opal_bitmap_t bm;
	char *str = NULL;
	bool is_set = false;

	construct(&bm);
	opal_bitmap_init(&bm, SIZE);

	opal_bitmap_set_bit(&bm, 1);
	printf("bitmap = %s\n", opal_bitmap_get_string(&bm));

	opal_bitmap_clear_bit(&bm, 1);
	printf("bitmap = %s\n", opal_bitmap_get_string(&bm));

	opal_bitmap_set_bit(&bm, 5);
	is_set = opal_bitmap_is_set_bit(&bm, 5);
	if (is_set)
		printf("5 is set, bitmap = %s\n", opal_bitmap_get_string(&bm));
	else
		printf("5 is not set, bitmap = %s\n", opal_bitmap_get_string(&bm));


	destruct(&bm);
	return 0;
}
