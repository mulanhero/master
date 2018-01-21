#include <iostream>
using namespace std;
/*
 Flags live in the ios class, manipulators lives in the std namespace, and the member functions live in the ostream class.
 */
int main() {
    cout.setf(ios::showpos | ios::uppercase); //turn on the ios::showpos flag
    cout << 27 << endl;

    cout.unsetf(ios::showpos);
    cout << 28 << endl;

    cout.unsetf(ios::dec); //turn off decimal output
    cout.setf(ios::hex);
    cout << "(27)16:" << 27 << endl;

    //turn on ios::oct as the only ios::basefield flag
    cout.setf(ios::oct, ios::basefield);
    cout << "(27)8:" << 27 << endl;

    return 0;
}
