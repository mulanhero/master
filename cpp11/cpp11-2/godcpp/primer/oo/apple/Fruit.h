/*
 * Fruit.h
 *
 *  Created on: Jul 15, 2014
 *      Author: jcao
 */

#ifndef FRUIT_H_
#define FRUIT_H_

#include <iostream>
using namespace std;

namespace libyarn {

class Fruit {
public:
    Fruit();
    Fruit(const Fruit& orig);
    virtual ~Fruit();
    Fruit(string &name);
    Fruit(string &name, float weight, float calories_per_oz);

    string& getName();

    void setWeight(float weight);
    float getWeight();

    void setCalariesPerOZ(float calories_per_oz);
    float getTotalCalory();

    float operator+(Fruit &f);
    virtual void peel();

    friend ostream& operator<<(ostream& out, Fruit &f);
    private:
    string name;
    float weight;
    float calories_per_oz;

};

} /* namespace libyarn */

#endif /* FRUIT_H_ */
