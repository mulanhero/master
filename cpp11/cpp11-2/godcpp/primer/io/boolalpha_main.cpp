#include <iostream>
using namespace std;

int main() {
    cout << true << " " << false << endl;

    cout.setf(ios::boolalpha);
    cout << true << " " << false << endl;

    cout << noboolalpha << true << " " << false << endl;
    cout << boolalpha << true << " " << false << endl;
    return 0;
}
