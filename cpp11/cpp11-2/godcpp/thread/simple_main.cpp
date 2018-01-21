#include <iostream>
#include <thread>

using namespace std;

void func() {
    cout << "Hi, my name is: Jimmy" << endl;
}

int main() {
    string myName("Jimmy");
    thread myThread(func);
    myThread.join();
    return 0;
}
