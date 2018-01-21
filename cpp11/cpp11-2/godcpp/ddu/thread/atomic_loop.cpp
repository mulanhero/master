#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<bool> is_ready(false);

void test() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    is_ready.store(true);
}

int main() {
    std::thread t(test);
    while(!is_ready.load()) {
        std::cout << "not ready yet!" << std::endl;
        std::this_thread::yield();
    }
    t.join();
    return 0;
}
