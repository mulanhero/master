#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    cout << -12345 << endl;
    cout << setw(10) << -12345 << endl;
    cout << setw(10) << left << -12345 << endl;
    cout << setw(10) << right << -12345 << endl;
    cout << setw(10) << internal << -12345 << endl;

    cout.fill('*');
    cout << -12345 << endl;
    cout << setw(10) << -12345 << endl;
    cout << setw(10) << left << -12345 << endl;
    cout << setw(10) << right << -12345 << endl;
    cout << setw(10) << internal << -12345 << endl;

    return 0;
}
