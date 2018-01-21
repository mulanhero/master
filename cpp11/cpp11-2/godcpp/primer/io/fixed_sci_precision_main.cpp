#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    cout << setprecision(3) << 123.456 << endl;
    cout << setprecision(4) << 123.456 << endl;
    cout << setprecision(5) << 123.456 << endl;
    cout << setprecision(6) << 123.456 << endl;
    cout << setprecision(7) << 123.456 << endl;

    cout << showpoint << endl;
    cout << setprecision(3) << 123.456 << endl;
    cout << setprecision(4) << 123.456 << endl;
    cout << setprecision(5) << 123.456 << endl;
    cout << setprecision(6) << 123.456 << endl;
    cout << setprecision(7) << 123.456 << endl;

    cout << fixed << endl;
    cout << setprecision(3) << 123.456 << endl;
    cout << setprecision(4) << 123.456 << endl;
    cout << setprecision(5) << 123.456 << endl;
    cout << setprecision(6) << 123.456 << endl;
    cout << setprecision(7) << 123.456 << endl;

    cout << scientific << endl;
    cout << setprecision(3) << 123.456 << endl;
    cout << setprecision(4) << 123.456 << endl;
    cout << setprecision(5) << 123.456 << endl;
    cout << setprecision(6) << 123.456 << endl;
    cout << setprecision(7) << 123.456 << endl;

    return 0;
}
