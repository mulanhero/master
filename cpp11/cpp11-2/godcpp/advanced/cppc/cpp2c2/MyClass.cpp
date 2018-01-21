/*
 * MyClass.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: jcao
 */

#include "MyClass.h"

namespace libyarn {

MyClass::MyClass(std::string &name) :
        name(name) {
}

std::string MyClass::getName() {
    return this->name;
}

MyClass::~MyClass() {
}

} /* namespace libyarn */
