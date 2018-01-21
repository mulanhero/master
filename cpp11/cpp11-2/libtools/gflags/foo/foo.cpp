/*
 * foo.cpp
 *
 *  Created on: 2014Äê9ÔÂ10ÈÕ
 *      Author: caohaijun
 */
#include "foo.h"

DECLARE_int32(port, 0, "What port to listen on");

bool validatePort(const char *flagName, int32_t value) {
	if (value > 0 && value < 32768) {
		return true;
	} else {
		printf("Invalid value for --%s: %d\n", flagName, (int)value);
		return false;
	}
}
