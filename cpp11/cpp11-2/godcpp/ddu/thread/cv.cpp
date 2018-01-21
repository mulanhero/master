#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
    std::unique_lock<std::mutex> lock(mtx);
  //  while (!ready) {
   //     cv.wait(lock);
 // }
    cv.wait(lock, [=](){return ready == true;});

    std::cout << "id" << id << std::endl;
}

void go() {
    std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    cv.notify_all();
}

int main() {

    std::thread threads[10];
    for (int i = 0; i < 10; ++i) {
        threads[i] = std::thread(print_id, i);
    }
    
    std::cout << "let all go:" << std::endl;
    go();

    for (auto& th : threads) {
        th.join();
    }
    return 0;
}
