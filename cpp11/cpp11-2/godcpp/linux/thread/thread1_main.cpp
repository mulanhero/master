#include <iostream>
#include <thread>

using namespace std;

void func() {
    for (int i = 0; i < 100; i++) {
        cout << i << "go" << endl;
    }
}

int main() {
    thread t(func);
    t.join();
    return 0;
}

