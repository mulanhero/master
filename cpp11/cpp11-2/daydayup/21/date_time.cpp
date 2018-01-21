#include <iostream>

int main() {
    std::cout << "try to use __DATE__ and __TIME:" 
        << __DATE__ << " "
        << __TIME__ << std::endl;
    return 0;
}
