#include "MyClass.h"
#include "MyCWrapper.h"

extern "C" {

MyClass* newMyClass(char *name) {
    std::string nameStr(name);
    return new MyClass(nameStr);
}

char *getName(MyClass *v) {
    std::string name = v->getName();

//	char *nameRT = new char[name.length() + 1];
//	strcpy(nameRT, name.c_str());
//	nameRT[name.size()] = '\0';

    char *nameRT = strdup(name.c_str());

    return nameRT;
}

void deleteMyClass(MyClass *v) {
    delete v;
}

}
