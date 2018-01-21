#include <iostream>
using namespace std;

/*
 Flags live in the ios class, manipulators lives in the std namespace, and the member functions live in the ostream class.
 */

int main() {
    cout << hex << 27 << endl;
    cout << 28 << endl;  //still in hex
    cout << dec << 29 << endl;
    return 0;
}
