#include "apple.h"

using namespace libyarn;
int main() {
    string name("apple");
    string color("red");
    Apple a1(name, 3.2, 5, color);
    cout << a1 << endl;
    a1.peel();

    Apple a2(name, 4.8, 5, color);
    float total = a1 + a2;
    cout << "apple: total:" << total << endl;

    return 0;
}
