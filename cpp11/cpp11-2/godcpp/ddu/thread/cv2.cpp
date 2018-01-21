#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready(false);

void test() {
    std::this_thread::sleep_for(std::chrono::seconds(30));
    std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    cv.notify_one();
}


int main() {
    std::thread t(test);
    std::unique_lock<std::mutex> lock(mtx);
    while (!ready) {
        cv.wait(lock);
        if (ready) {
            std::cout << "wake up!" << std::endl;
            
        }
    }
    t.join();
    return 0;
}
