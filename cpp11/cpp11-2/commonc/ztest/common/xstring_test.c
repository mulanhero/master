/*
 * xstring_test.c
 *
 *  Created on: Mar 4, 2013
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>

#include "src/common/xstring.h"
#include "src/common/xmalloc.h"

/**
 * char *xbasename(char *path);
 */
void xbasename_test()
{
	char *path = "/usr/local/bin";
	char *base = NULL;
	base = xbasename(path);
	puts(base);
}
/**
#include <libgen.h>
char *dirname(char *path);
char *basename(char *path);
 */
void __basename_dirname_test()
{
	char *path = "/usr/local/bin";
	char *cp_path_for_base = NULL;
	char *cp_path_for_dir = NULL;

	char *base = NULL;
	char *dir = NULL;

	cp_path_for_base = xstrdup(path);
	base = basename(cp_path_for_base);
	puts(base);
	xfree(cp_path_for_base);

	cp_path_for_dir = xstrdup(path);
	dir = dirname(cp_path_for_dir);
	puts(dir);
	xfree(cp_path_for_dir);
}


/**
 * char *xshort_hostname(void);
 *
 */
void xshort_hostname_test(void)
{
	char *short_hn;
	short_hn = xshort_hostname();
	puts(short_hn);
	xfree(short_hn);
}

/**
 * char *xstrdup(const char *str);
 */
void xstrdup_test()
{
	char *str = NULL;
	str = xstrdup("Jimmy, fighting!!");
	puts(str);
	xfree(str);
}

/**
char *xstrdup_printf(const char *fmt, ...)
  __attribute__ ((format (printf, 1, 2)));
 */
void xstrdup_printf_test()
{
	char *result = NULL;
	result = xstrdup_printf("my age is %d, name = %s", 32, "jimmy");
	puts(result);
	xfree(result);
}

/**
 * bool xstring_is_whitespace(const char *str);
 */
void xstring_is_whitespace_test()
{
	char *white_str = "        ";
	bool result = false;

	result = xstring_is_whitespace(white_str);
	if(true == result)
		puts("is whitespace");
	else
		puts("is not whitespace");
}


/**
 * char *xstrndup(const char *str, size_t n);
 */
void xstrndup_test()
{
	char *result = NULL;
	result = xstrndup("123456789", 2);
	puts(result);
	xfree(result);
}

/**
 * long int xstrntol(const char *str, char **endptr, size_t n, int base);
 */
void xstrntol_test()
{
	long result = 0;
	char *endptr = NULL;

	result = xstrntol("123456789 abcdef", &endptr, 8, 10);

	printf("result = %ld\n", result);
	/* sth wrong with endptr */
}


void __strtol_test()
{
	char szNumbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
	char *pEnd;
	long int li1, li2, li3, li4;

	li1 = strtol (szNumbers,&pEnd,10);
	puts(pEnd);

	li2 = strtol (pEnd,&pEnd,16);
	puts(pEnd);

	li3 = strtol (pEnd,&pEnd,2);
	puts(pEnd);

	li4 = strtol (pEnd,&pEnd,0);
	if (*pEnd == '\0')
		puts("*pEnd == \'\\0\'");
	else
		puts(pEnd);

	printf ("The decimal equivalents are: %ld, %ld, %ld and %ld.\n", li1, li2, li3, li4);
}

/**
 * char *xstrstrip(char *str);
 */
void xstrstrip_test()
{
	//todo
}

/**
 * char *xstrtolower(char *str);
 */
void xstrtolower_test()
{
	char *origin = xstrdup("Jimmy Cao");
	char *lower = NULL;
	lower = xstrtolower(origin);
	puts(origin);
	puts(lower);
	xfree(origin);
}

/**
 * void _xmemcat(char **str, char *start, char *end);
 */
void _xmemcat_test()
{
//todo
}

/**
 * void _xrfc5424timecat(char **str);
 */
void _xrfc5424timecat_test()
{
	char *str = NULL;

	str = xstrdup("This is jimmy");
	_xrfc5424timecat(&str);

	puts(str);
	xfree(str);
}

/**
 * void _xslurm_strerrorcat(char **str);
 */
//todo

/**
 * void _xstrcat(char **str1, const char *str2);
 */
void _xstrcat_test()
{
	char *str1 = xstrdup("jimmy ");
	char *str2 = "cao";
	_xstrcat(&str1, str2);
	puts(str1);
	xfree(str1);
}

/*
 * void _xstrcatchar(char **str1, char c);
 */
void _xstrcatchar_test()
{
	char *str1 = xstrdup("jimmy ");
	char c = '!';

	_xstrcatchar(&str1, c);
	puts(str1);
	xfree(str1);
}

/**
 * int _xstrfmtcat(char **str, const char *fmt, ...)
  __attribute__ ((format (printf, 2, 3)));
 */
void _xstrfmtcat_test()
{
	char *str = xstrdup("Hi, ");
	_xstrfmtcat(&str, "your age = %d, name = %s", 32, "jimmy");

	puts(str);
	xfree(str);
}

/**
 * void _xstrftimecat(char **str, const char *fmt);
 */
void _xstrftimecat_test()
{
	char *str = xstrdup("jimmy");
	_xstrftimecat(&str, "%Y-%m-%d-%H-%M-%S");
	puts(str);
	xfree(str);
}

/**
 * void _xstrncat(char **str1, const char *str2, size_t len);
 */
void _xstrncat_test()
{
	char *target = xstrdup("Jimmy ");
	_xstrncat(&target, "Cao, Fighting!!!! 123!", 3);
	puts(target);
	xfree(target);
}

/*
 * void _xstrsubstitute(char **str, const char *pattern, const char *replacement);
XIAN wuhan BEIJING SHANGHAI WUHAN
 */
void _xstrsubstitute_test()
{
	char *str = xstrdup("XIAN WUHAN BEIJING SHANGHAI WUHAN");
	_xstrsubstitute(&str, "WUHAN", "wuhan");
	puts(str);
	xfree(str);
}

int main()
{
#if 0
	xbasename_test();
	__basename_dirname_test();
	xshort_hostname_test();
	xstrdup_test();
	xstrdup_printf_test();
	xstring_is_whitespace_test();
	xstrndup_test();
	xstrntol_test();
	__strtol_test();
	xstrstrip_test();
	xstrtolower_test();
	_xmemcat_test();
	_xrfc5424timecat_test();
	_xstrcat_test();
	_xstrcatchar_test();
	_xstrfmtcat_test();
	_xstrftimecat_test();
	_xstrncat_test();
#endif

	_xstrsubstitute_test();
	return 0;
}

