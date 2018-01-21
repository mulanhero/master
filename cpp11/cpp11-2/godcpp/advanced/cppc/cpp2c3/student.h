/*
 * student.h
 *
 *  Created on: Jun 9, 2014
 *      Author: caoj7
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>

class student {
public:
    student(std::string &name);
    void talk();
    private:
    std::string name;
};

#endif /* STUDENT_H_ */
