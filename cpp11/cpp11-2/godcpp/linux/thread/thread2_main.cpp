#include <string>
#include <iostream>
#include <thread>

using namespace std;

//The function we want to make the thread run.
void task1(string msg) {
    for (int i = 0; i < 100; i++) {
        cout << i << "in task1, task1 says: " << msg << endl;
    }
}

int main() {
    // Constructs the new thread and runs it. Does not block execution.
    thread t1(task1, "Hello");

    for (int i = 0; i < 100; i++) {
        cout << "in main:" << i << endl;
    }
    //Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    t1.join();
    return 0;
}
