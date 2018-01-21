/*
 * MyCWrapper.h
 *
 *  Created on: Jul 8, 2014
 *      Author: jcao
 */

#ifndef MYCWRAPPER_H_
#define MYCWRAPPER_H_

#include "MyClass.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef class libyarn::MyClass MyClass;

MyClass *newMyClass(char *name);

char *getName(MyClass *v);

void deleteMyClass(MyClass *v);

#ifdef __cplusplus
}
#endif

#endif /* MYCWRAPPER_H_ */
