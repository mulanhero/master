#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/util/argv.h"
#include "src/util/constants.h"

/**
 * extern int argv_append(int *argc, char ***argv, const char *arg);
 * output:
first_str
second_str
argc = 2
 */
void argv_append_test()
{
	char **argv = NULL;
	char **argv_tmp = NULL;
	int argc = 0;

	argv_append(&argc, &argv, "first_str");
	argv_append(&argc, &argv, "second_str");
	/* argv_tmp will be freed */
	argv_tmp = argv;

	while (*argv)
		puts(*argv++);

	argv_free(argv_tmp);

	printf("argc = %d\n", argc);
}


/**
 * extern  int argv_append_nosize(char ***argv, const char *arg);
 * output:
first_str
second_str
 */
void argv_append_nosize_test()
{
	char **argv = NULL;
	char **argv_tmp = NULL;

	argv_append_nosize(&argv, "first_str");
	argv_append_nosize(&argv, "second_str");
	/* argv_tmp will be freed */
	argv_tmp = argv;

	while (*argv)
		puts(*argv++);

	argv_free(argv_tmp);
}

/**
 * extern  int argv_append_unique_nosize(char ***argv,
 * 					const char *arg, bool overwrite);
 * output:
first_str
second_str
third_str
 */

void argv_append_unique_nosize_test()
{
	char **argv = NULL;
	char **argv_tmp = NULL;

	argv_append_unique_nosize(&argv, "first_str", true);
	argv_append_unique_nosize(&argv, "second_str", true);
	argv_append_unique_nosize(&argv, "third_str", true);
	argv_append_unique_nosize(&argv, "first_str", true);
	argv_append_unique_nosize(&argv, "first_str", true);
	/* argv_tmp will be freed */
	argv_tmp = argv;

	while (*argv)
			puts(*argv++);

	argv_free(argv_tmp);
}

/**
 * extern char **argv_copy(char **argv);
first_str
second_str
third_str
forth_str
 */
void argv_copy_test()
{
	char **source = NULL;
	char **target = NULL;
	char **tmp_target = NULL;

	argv_append_nosize(&source, "first_str");
	argv_append_nosize(&source, "second_str");
	argv_append_nosize(&source, "third_str");
	argv_append_nosize(&source, "forth_str");

	target = argv_copy(source);
	tmp_target = target;
	while(*tmp_target)
		puts(*tmp_target++);

	argv_free(target);
	argv_free(source);
}

/**
 * extern  int argv_count(char **argv);
argv_count(argv) = 3
 */
void argv_count_test()
{
	char **argv = NULL;
	char **tmp_argv = NULL;
	int count = 0;

	argv_append_unique_nosize(&argv, "first_str", true);
	argv_append_unique_nosize(&argv, "second_str", true);
	argv_append_unique_nosize(&argv, "third_str", true);
	argv_append_unique_nosize(&argv, "first_str", true);
	argv_append_unique_nosize(&argv, "first_str", true);
	/* argv_tmp will be freed */
	tmp_argv = argv;

	count = argv_count(argv);
	printf("argv_count(argv) = %d\n", count);

	argv_free(tmp_argv);
}

/**
 * extern  int argv_delete(int *argc, char ***argv,
                                    int start, int num_to_delete);

 * output:
the original argv:
first_str
second_str
third_str
forth_str
after deleting, argv:
first_str
second_str
 */

void argv_delete_test()
{
	char **argv = NULL;
	char **tmp_argv = NULL;
	int argc = 0;

	argv_append_nosize(&argv, "first_str");
	argv_append_nosize(&argv, "second_str");
	argv_append_nosize(&argv, "third_str");
	argv_append_nosize(&argv, "forth_str");

	tmp_argv = argv;
	puts("the original argv:");
	while(*tmp_argv)
		puts(*tmp_argv++);

	/* tmp_argv will be freed */
	tmp_argv = argv;
	argv_delete(&argc, &argv, 2, 2);
	puts("after deleting, argv:");
	while(*argv)
		puts(*argv++);

	argv_free(tmp_argv);
}

/**
 * extern  int argv_insert(char ***target, int start, char **source);
the original target:
first_str
second_str
third_str
forth_str
the original source:
1st
2nd
after inserting, new target:
first_str
second_str
1st
2nd
third_str
forth_str
 */
void argv_insert_test()
{
	char **target = NULL;
	char **tmp_target = NULL;
	char **source = NULL;
	char **tmp_source = NULL;

	argv_append_nosize(&target, "first_str");
	argv_append_nosize(&target, "second_str");
	argv_append_nosize(&target, "third_str");
	argv_append_nosize(&target, "forth_str");

	puts("the original target:");
	tmp_target = target;
	while (*tmp_target)
		puts(*tmp_target++);

	argv_append_nosize(&source, "1st");
	argv_append_nosize(&source, "2nd");

	puts("the original source:");
	tmp_source = source;
	while (*tmp_source)
		puts(*tmp_source++);

	argv_insert(&target, 2, source);

	puts("after inserting, new target:");
	tmp_target = target;
	while (*tmp_target)
		puts(*tmp_target++);

	argv_free(target);
	argv_free(source);
}

/**
 * extern  int argv_insert_element(char ***target, int location, char *source);
the original target:
first_str
second_str
third_str
forth_str
after inserting, new target:
first_str
second_str
2nd
third_str
forth_str
 */
void argv_insert_element_test()
{
	char **target = NULL;
	char **tmp_target = NULL;

	argv_append_nosize(&target, "first_str");
	argv_append_nosize(&target, "second_str");
	argv_append_nosize(&target, "third_str");
	argv_append_nosize(&target, "forth_str");

	puts("the original target:");
	tmp_target = target;
	while (*tmp_target)
		puts(*tmp_target++);

	argv_insert_element(&target, 2, "2nd");

	puts("after inserting, new target:");
	tmp_target = target;
	while (*tmp_target)
		puts(*tmp_target++);

	argv_free(target);
}

/**
 * extern  char *argv_join(char **argv, int delimiter) ;
first_str:second_str:third_str:forth_str
 */
void argv_join_test()
{
	char *result = NULL;
	char **argv = NULL;

	argv_append_nosize(&argv, "first_str");
	argv_append_nosize(&argv, "second_str");
	argv_append_nosize(&argv, "third_str");
	argv_append_nosize(&argv, "forth_str");

	result = argv_join(argv, ':');
	puts(result);

	free(result); /* Note: free */
	argv_free(argv);
}

/**
 * extern char *argv_join_range(char **argv, size_t start, size_t end,
			     int delimiter);
second_str:third_str
 */
void argv_join_range_test()
{
	char *result = NULL;
	char **argv = NULL;

	argv_append_nosize(&argv, "first_str");
	argv_append_nosize(&argv, "second_str");
	argv_append_nosize(&argv, "third_str");
	argv_append_nosize(&argv, "forth_str");

	result = argv_join_range(argv, 1, 3, ':');
	puts(result);

	free(result); /* Note: free */
	argv_free(argv);
}

/**
 * extern  size_t argv_len(char **argv);
argv_len(argv) = 81
total_length = 81
 */
void argv_len_test()
{
	char **argv = NULL;
	size_t length = 0;
	size_t total_length = 0;

	argv_append_nosize(&argv, "first_str");
	argv_append_nosize(&argv, "second_str");
	argv_append_nosize(&argv, "third_str");
	argv_append_nosize(&argv, "forth_str");

	length = argv_len(argv);
	printf("argv_len(argv) = %d\n", length);


	total_length += strlen("first_str") + 1 + sizeof(char *);
	total_length += strlen("second_str") + 1 + sizeof(char *);
	total_length += strlen("third_str") + 1 + sizeof(char *);
	total_length += strlen("forth_str") + 1 + sizeof(char *);
	total_length += sizeof(char *);
	printf("total_length = %d\n", total_length);

	argv_free(argv);
}

/**
 * extern int argv_prepend_nosize(char ***argv, const char *arg);
after prepending:
zero_str
first_str
second_str
 */
void argv_prepend_nosize_test()
{
	char **argv = NULL;

	argv_append_nosize(&argv, "first_str");
	argv_append_nosize(&argv, "second_str");

	argv_prepend_nosize(&argv, "zero_str");

	puts("after prepending:");
	while(*argv)
		puts(*argv++);
}


/**
 * extern  char **argv_split(const char *src_string, int delimiter);
first
second
third

forth
 */
void argv_split_test()
{
	char str[] = "first:second:third: ::forth";
	char **argv = NULL;
	char **tmp_argv = NULL;

	argv = argv_split(str, ':');
	tmp_argv = argv;

	while(*tmp_argv)
		puts(*tmp_argv++);

	argv_free(argv);
}

/**
 * extern  char **argv_split_with_empty(const char *src_string, int delimiter) ;
first
second
third

		//this is the empty string
forth
 */
void argv_split_with_empty_test()
{
	char str[] = "first:second:third: ::forth";
	char **argv = NULL;
	char **tmp_argv = NULL;

	argv = argv_split_with_empty(str, ':');
	tmp_argv = argv;

	while(*tmp_argv)
		puts(*tmp_argv++);

	argv_free(argv);
}

int main(void) {
#if 0
	argv_append_test();
	argv_append_nosize_test();
	argv_append_unique_nosize_test();
	argv_copy_test();
	argv_count_test();
	argv_delete_test();
	argv_insert_test();
	argv_insert_element_test();
	argv_join_test();
	argv_join_range_test();
	argv_len_test();
	argv_prepend_nosize_test();
	argv_split_test();
#endif

	argv_split_with_empty_test();
	return 0;
}
