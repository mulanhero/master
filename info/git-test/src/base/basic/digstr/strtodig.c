/*
 * strtodit.c
 *
 *  Created on: Dec 21, 2012
 *      Author: caoj7
 */
#if HAVE_CONFIG_H
#  include "config.h"
#  if HAVE_INTTYPES_H
#    include <inttypes.h>
#  else
#    if HAVE_STDINT_H
#      include <stdint.h>
#    endif
#  endif  /* HAVE_INTTYPES_H */
#else   /* !HAVE_CONFIG_H */
#  include <inttypes.h>
#endif  /*  HAVE_CONFIG_H */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]){
	uint16_t port;
	uint32_t headcount;

	port = atoi("5555");
	printf("port = %u\n", port);

	headcount = strtoul("999999", NULL, 10);
	printf("headcount = %lu\n", headcount);
	return 0;
}
