#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));

    string serialNum;
    serialNum.reserve(64);

    for (int i = 0; i < 64; i++) {
        serialNum += 'a' + rand() % 26;
    }

    cout << serialNum << endl;
    return 0;
}
