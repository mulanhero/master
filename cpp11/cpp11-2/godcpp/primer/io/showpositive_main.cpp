#include <iostream>
using namespace std;

int main() {
    cout << 5 << endl;

    cout.setf(ios::showpos);
    cout << 5 << endl;

    cout << noshowpos << 5 << endl;
    cout << showpos << 5 << endl;
    return 0;
}
