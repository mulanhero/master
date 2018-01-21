#include <iostream>

#include "Fruit.h"

using namespace std;
using namespace libyarn;

int main() {
    std::string name("orange");
    Fruit f1(name, 1.5, 10);
    cout << "f1: total Calories:" << f1.getTotalCalory() << endl;

    Fruit f2(name, 2.5, 10);
    cout << "f2: total Calories:" << f2.getTotalCalory() << endl;

    float total = f1 + f2;
    cout << "total weight:" << total << endl;
    return 0;
}
