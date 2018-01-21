/*
 * Printer.h
 *
 *  Created on: Jul 15, 2014
 *      Author: jcao
 */

#ifndef PRINTER_H_
#define PRINTER_H_

#include "PoweredDevice.h"

class Printer : virtual public PoweredDevice {  //virtual
private:
    int id;
    public:
    Printer(int power, int id) :
            PoweredDevice(power), id(id) {
    }

    int getId() {
        return this->id;
    }
};

#endif /* PRINTER_H_ */
