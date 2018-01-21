#include <stdio.h>
#include <stdlib.h>
#include "wrapper.h"

int main() {
    char *name = "jimmy";
    student* stu = newStudent(name);
    talk(stu);
    deleteStudent(stu);

    return 0;
}
