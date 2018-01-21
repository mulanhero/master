#include <stdio.h>
#include <stdlib.h>

#if HAVE_STDBOOL_H
#  include <stdbool.h>
#else
typedef enum {false, true} bool;
#endif /* !HAVE_STDBOOL_H */

void delim_with_comma(char **argv)
{
	char *result = NULL, *tmp;
	int flag = true;


	while(*argv){
		if(flag == true){
			asprintf(&result, "%s", *argv);
			flag = false;
		}else{
			tmp = result;
			asprintf(&result, "%s,%s", tmp, *argv);
			/* to prevent memory leak */
			free(tmp);
		}
		argv++;
	}
	printf("result = %s\n", result);
	/* to prevent memory leak */
	free(result);
}

int main()
{
	char *argv[] = {"beijing", "shanghai", "wuhan", "xian", NULL};
	delim_with_comma(argv);
	return 0;
}
