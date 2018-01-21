#include <iostream>
#include <cmath>
#include <chrono>
#include <unistd.h>


int main() {
    using std::chrono::time_point;
    using std::chrono::system_clock;
    using std::chrono::steady_clock;
    using std::chrono::duration;
    using std::chrono::minutes;

    std::chrono::time_point<system_clock, duration<int>> tp_seconds(duration<int>(1));
    std::time_t tt = system_clock::to_time_t(tp_seconds);
    std::cout << "tp_seconds is:" << ctime(&tt) << std::endl;

    system_clock::time_point tp;
    tp += minutes(10);
    std::cout << tp.time_since_epoch().count() << " system_clock periods" << std::endl;



    
}
