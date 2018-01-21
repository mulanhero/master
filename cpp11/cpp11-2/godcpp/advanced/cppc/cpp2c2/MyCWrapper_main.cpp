#include <stdio.h>
#include <stdlib.h>
#include "MyCWrapper.h"

int main() {
    char *name = "jimmy";
    MyClass *myClass = newMyClass(name);
    char * nameRT = getName(myClass);
    printf("nameRT = %s\n", nameRT);
    free(nameRT);
    deleteMyClass(myClass);
    return 0;
}
