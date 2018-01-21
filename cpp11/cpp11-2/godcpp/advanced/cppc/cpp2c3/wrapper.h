#ifndef WRAPPER_H_
#define WRAPPER_H_

#include "student.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef class student student;

student* newStudent(char *name);

void talk(student* v);

void deleteStudent(student* v);

#ifdef __cplusplus
}
#endif

#endif /* WRAPPER_H_ */
