/*
 * Scanner.h
 *
 *  Created on: Jul 15, 2014
 *      Author: jcao
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include "PoweredDevice.h"

class Scanner : virtual public PoweredDevice {  //virtual
private:
    int id;

public:
    Scanner(int power, int id) :
            PoweredDevice(power), id(id) {
    }

    int getId() {
        return this->id;
    }
};

#endif /* SCANNER_H_ */
