/*
 * foo.h
 *
 *  Created on: 2014��9��10��
 *      Author: caohaijun
 */

#ifndef FOO_H_
#define FOO_H_

#include <iostream>
#include <gflags/gflags.h>

DECLARE_int32(port);

bool validatePort(const char *flagName, int32_t value);


#endif /* FOO_H_ */
