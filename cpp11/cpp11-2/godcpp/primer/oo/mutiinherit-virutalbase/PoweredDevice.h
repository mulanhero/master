/*
 * PoweredDevice.h
 *
 *  Created on: Jul 15, 2014
 *      Author: jcao
 */

#ifndef POWEREDDEVICE_H_
#define POWEREDDEVICE_H_

class PoweredDevice {
private:
    int power;
    public:
    PoweredDevice(int power) :
            power(power) {
    }

    int getPower() {
        return this->power;
    }
};

#endif /* POWEREDDEVICE_H_ */
