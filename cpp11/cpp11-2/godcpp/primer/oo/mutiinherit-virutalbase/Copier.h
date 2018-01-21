/*
 * Copier.h
 *
 *  Created on: Jul 15, 2014
 *      Author: jcao
 */

#ifndef COPIER_H_
#define COPIER_H_

#include <iostream>

#include "Printer.h"
#include "Scanner.h"
#include "PoweredDevice.h"

using namespace std;

/*
 PoweredDevice only gets constructed once.

 Because both Printer and Scanner are ' : virtual public ' PoweredDevice.h
 */
class Copier : public Printer, public Scanner {
private:
    int id;
    public:
    Copier(int power, int printerId, int scannerId, int id) :
            PoweredDevice(power), Printer(power, printerId), Scanner(power,
                    scannerId), id(id) {
    }

    int getId() {
        return this->id;
    }

    friend ostream& operator<<(ostream& out, Copier &c);

};

ostream& operator<<(ostream& out, Copier &c) {
    out << "power:" << c.PoweredDevice::getPower() << ", printerId:" << c.Printer::getId()
            << ", scannerId:" << c.Scanner::getId() << ", id:" << c.getId();
    return out;
}

#endif /* COPIER_H_ */
