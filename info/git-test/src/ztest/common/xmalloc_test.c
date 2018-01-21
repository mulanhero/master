#include <stdio.h>
#include <stdlib.h>
#include "src/common/xmalloc.h"
#include "src/common/xstring.h"

typedef struct {
	int age;
	char *name;
} person_t;

/**
 *	xmalloc(__sz)
 *	xfree(__p)
 *	xrealloc(__p, __sz)
 *	xsize(__p)
 */
void xmalloc_xrealloc_xsize_xfree()
{
	person_t *pt = NULL;

	/* xmalloc need xfree !*/
	pt = xmalloc(sizeof(person_t));

	pt->age = 0;
	/* Note: xstrdup needs xfree! */
	pt->name = xstrdup("baby");

	/* xsize(pt) to get the size of allocated memory */
	printf("xsize(pt) = %d\n", xsize(pt));
	printf("sizeof(person_t) = %d\n", sizeof(person_t));
	printf("age = %d, name = %s\n", pt->age, pt->name);

	/* now let's xrealloc */
	pt->name = xrealloc(pt->name, 256);
	/* since memory has been expanded, strcpy is ok. */
	strcpy(pt->name, "now baby's name is VERYLONG");
	printf("after xrealloc, age = %d, name = %s\n", pt->age, pt->name);

	/* Note: xfree(pt->name) first! */
	xfree(pt->name);
	xfree(pt);
}

int main()
{
	xmalloc_xrealloc_xsize_xfree();
	return 0;
}
