#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/util/argv.h"
#include "src/util/common.h"

/*
 * extern  char **argv_split(const char *src_string, int delimiter);
 * extern  void argv_free(char **argv);
 * extern  int argv_append_nosize(char ***argv, const char *arg);
 * int  argv_count(char **argv);
 * Note: the caller is reponsible for free(port_array);
 */
int convert_m(char *range, uint32_t **port_array, int *size)
{
	*size = 0;
	char **argv = NULL;
	char **tmp_argv = NULL;
	char **result_argv = NULL;
	char **tmp_result_argv = NULL;
	uint32_t min = 0;
	uint32_t max = 0;
	char *pos = NULL;
	char port_str[32] = "";
	int i = 0;

	/* add each element within range as a string to result_argv*/
	argv = argv_split(range, ',');
	tmp_argv = argv;
	while (*tmp_argv) {
		if (strchr(*tmp_argv, '-')) {
			min = strtoul(*tmp_argv, &pos, 10);
			max = strtoul(pos+1, NULL, 10);
			for (; min <= max; min++) {
				snprintf(port_str, 32, "%lu", min);
				argv_append_nosize(&result_argv, port_str);
			}
		} else {
			argv_append_nosize(&result_argv, *tmp_argv);
		}
		tmp_argv++;
	}

	*size = argv_count(result_argv);
	printf("*size = %d\n", *size);

	*port_array = (uint32_t *)malloc(sizeof(uint32_t) * *size);
	if (NULL == *port_array)
		return 1;
	memset(*port_array, 0, sizeof(uint32_t) * *size);
	tmp_result_argv = result_argv;
	i = 0;
	while (*tmp_result_argv) {
		*(*port_array + i) = strtoul(*tmp_result_argv, NULL, 10);
		tmp_result_argv++;
		i++;
	}

	argv_free(argv);
	argv_free(result_argv);
	return 0;
}

int main()
{
	char *range = "12001,12003-12005,12007";
	uint32_t *port_array = NULL;
	int size = 0;
	int i, rc;

	rc = convert_m(range, &port_array, &size);
	if (!rc) {
		for (i = 0; i < size; i++)
			printf("port_array[%d] = %lu\n", i, *(port_array+i));
		free(port_array);
	}

	return 0;
}
