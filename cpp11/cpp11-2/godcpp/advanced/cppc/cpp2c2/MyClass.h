#ifndef MYCLASS_H_
#define MYCLASS_H_

#include <iostream>

namespace libyarn {

class MyClass {
public:
    MyClass(std::string &name);

    std::string getName();

    virtual ~MyClass();
    private:
    std::string name;
};

} /* namespace libyarn */

#endif /* MYCLASS_H_ */
