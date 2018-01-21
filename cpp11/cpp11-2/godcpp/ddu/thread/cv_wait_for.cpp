#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;
int value = 999;

void get_input() {
    std::cin >> value;
    cv.notify_one();
}

int main() {
    std::cout << "please enter an integer:";
    std::thread th(get_input);

    std::unique_lock<std::mutex> lock(mtx);
    if(cv.wait_for(lock, std::chrono::seconds(1)) == std::cv_status::timeout) {
        std::cout << "timeout, default value:" << value << std::endl;        
        th.interrupt();
    } else {
        std::cout << "your enter:" << value << std::endl;
        th.join();
    }

    return 0;
}
