#include <iostream>
using namespace std;
/* Note: get() is that it does not read in a newline character */
int main() {
    char buf[11];
    cin.get(buf, 11);
    cout << buf << endl;

    char ch;
    while (cin.get(ch)) {
        cout << ch;
    }

    return 0;
}
