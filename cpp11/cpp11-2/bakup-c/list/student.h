/*
 * student.h
 *
 *  Created on: Sep 11, 2012
 *      Author: caoj7
 */

#ifndef STUDENT_H_
#define STUDENT_H_

typedef struct student{
	int age;
	char name[20];
	struct student *next;
}STUDENT;


#endif /* STUDENT_H_ */
