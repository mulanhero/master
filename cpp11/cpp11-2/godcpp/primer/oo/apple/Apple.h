/*
 * Apple.h
 *
 *  Created on: Jul 15, 2014
 *      Author: jcao
 */

#ifndef APPLE_H_
#define APPLE_H_

#include "Fruit.h"

namespace libyarn {

class Apple : public Fruit {
public:
    Apple();
    Apple(const Apple& orig);
    Apple(string name, float weight, float calories_per_oz, string color);
    virtual ~Apple();

    void setColor(string &color);
    string getColor();

    friend ostream& operator<<(ostream& out, Apple &a);

    void peel(); //override the virtual func

private:
    string color;
};

} /* namespace libyarn */

#endif /* APPLE_H_ */
