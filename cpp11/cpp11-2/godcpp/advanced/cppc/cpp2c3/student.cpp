#include "student.h"
#include <iostream>

student::student(std::string &name) {
    this->name = name;
}

void student::talk() {
    std::cout << "I am " << this->name << std::endl;
}

