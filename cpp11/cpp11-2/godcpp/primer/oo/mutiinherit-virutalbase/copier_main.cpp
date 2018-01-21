/*
 * copier_main.cpp
 *
 *  Created on: Jul 15, 2014
 *      Author: jcao
 */

#include "Copier.h"

int main() {
    int power = 5;
    int printerId = 9;
    int scannerId = 99;
    int id = 999;
    Copier c(power, printerId, scannerId, id);
    cout << c << endl;

    return 0;
}

