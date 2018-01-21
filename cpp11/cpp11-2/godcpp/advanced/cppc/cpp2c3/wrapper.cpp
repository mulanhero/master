#include "student.h"
#include "wrapper.h"

student* newStudent(char *name) {
    std::string nameStr(name);
    return new student(nameStr);
}

void talk(student *v) {
    return v->talk();
}

void deleteStudent(student *v) {
    delete v;
}
