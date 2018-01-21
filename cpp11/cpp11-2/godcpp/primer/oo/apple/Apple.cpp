/*
 * Apple.cpp
 *
 *  Created on: Jul 15, 2014
 *      Author: jcao
 */

#include "Apple.h"

namespace libyarn {

Apple::Apple() {
}

Apple::Apple(string name, float weight, float calories_per_oz, string color) :
        Fruit(name, weight, calories_per_oz), color(color) {
}

Apple::~Apple() {
}

void Apple::setColor(string &color) {
    this->color = color;
}

string Apple::getColor() {
    return this->color;
}

void Apple::peel() {
    cout << "remove the peel in Apple.cpp ..." << endl;
}

ostream& operator<<(ostream& out, Apple &a) {
    out << "name:" << a.getName() << ", weight:" << a.getWeight()
            << ", totalCalory:" << a.getTotalCalory() << ", color:" << a.getColor();
    return out;
}

} /* namespace libyarn */
