#include <iostream>
using namespace std;

int main() {
    //flag: basefield
    cout << 27 << endl;

    cout.setf(ios::dec, ios::basefield);
    cout << 27 << endl;

    cout.setf(ios::oct, ios::basefield);
    cout << 27 << endl;

    cout.setf(ios::hex, ios::basefield);
    cout << 27 << endl;

    //manipulator
    cout << dec << 27 << endl;
    cout << oct << 27 << endl;
    cout << hex << 27 << endl;
    return 0;
}
