/*
 * Fruit.cpp
 *
 *  Created on: Jul 15, 2014
 *      Author: jcao
 */
#include "Fruit.h"

namespace libyarn {

Fruit::Fruit() {
}

Fruit::~Fruit() {
}

Fruit::Fruit(string &name) :
        name(name) {
}

Fruit::Fruit(string &name, float weight, float calories_per_oz) :
        name(name), weight(weight), calories_per_oz(calories_per_oz) {
}

string& Fruit::getName() {
    return this->name;
}

void Fruit::setWeight(float weight) {
    this->weight = weight;
}

float Fruit::getWeight() {
    return this->weight;
}

void Fruit::setCalariesPerOZ(float calories_per_oz) {
    this->calories_per_oz = calories_per_oz;
}

float Fruit::getTotalCalory() {
    return this->calories_per_oz * this->weight;
}

float Fruit::operator +(Fruit &f) {
    return this->weight + f.weight;
}

void Fruit::peel() {
    cout << "remove the peel in Fruit.cpp" << endl;
}

ostream& operator<<(ostream& out, Fruit &f) {
    out << "name:" << f.name << ", weight:" << f.weight
            << ", totalCalories:" << f.getTotalCalory();
    return out;
}

} /* namespace libyarn */
