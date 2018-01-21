#include <stdio.h>
#include <stdlib.h>

#define s_asprintf(write_to, ...)	{ 	\
	char *tmp;							\
	tmp = write_to;						\
	asprintf(&(write_to), __VA_ARGS__);	\
	free(tmp);							\
}


int main()
{
	char *str;
	s_asprintf(str, "select * from");
	s_asprintf(str, "%s where id = %d", str, 992);
	puts(str);
	free(str);
	return 0;
}
