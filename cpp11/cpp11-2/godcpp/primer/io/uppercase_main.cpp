#include <iostream>
using namespace std;

int main() {
    cout << 12345678.9 << endl;

    cout.setf(ios::uppercase);
    cout << 12345678.9 << endl;

    cout << nouppercase << 12345678.9 << endl;
    cout << uppercase << 12345678.9 << endl;

    return 0;
}
