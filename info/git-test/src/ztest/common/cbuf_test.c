/*
 * cbuf_test.c
 *
 *  Created on: Mar 3, 2013
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/common/cbuf.h"
/**
 * cbuf_t cbuf_create (int minsize, int maxsize);
 *
 * int cbuf_write (cbuf_t dst, void *srcbuf, int len, int *ndropped);
 *
 * int cbuf_read_to_fd (cbuf_t src, int dstfd, int len);
 *
 * void cbuf_destroy (cbuf_t cb);
 *
 *
 *	cbuf_write(cb, buf, len, &dropped);
		cbuf_read_to_fd(cb, fd, -1);
 *
 */

int cbuf_create_destroy()
{
	FILE *fp = NULL;
	int fd = -1;
	/*Note: cb is a instance of (struct cbuf *) */
	cbuf_t cb = NULL;
	char *info = "[info:] this is a info log.\n";
	int dropped = -1;
	int n = 0;


	if (NULL == (fp = fopen("jimmy.log", "a+"))) {
		perror("fopen");
		exit -1;
	}

	if (0 > (fd = fileno(fp))) {
		exit -1;
	}

	cb = cbuf_create(128, 8192);
	n = cbuf_write(cb, info, strlen(info), &dropped);
	if (n > 0) {
		printf("strlen(info) = %d, n = %d has been written into cb.\n", strlen(info), n);
	}

	if (0 < cbuf_used(cb)) {
		cbuf_read_to_fd(cb, fd, -1);
		cbuf_read_to_fd(cb, 1, -1);  // also read to fd = 1 (stdout)
	}

	fclose(fp);
	cbuf_destroy(cb);

	return 0;
}


int main()
{
#if 0
#endif

	cbuf_create_destroy();
	return 0;
}
