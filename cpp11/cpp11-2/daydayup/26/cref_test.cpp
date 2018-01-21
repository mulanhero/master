#include <iostream>
#include <functional>


void print(const int& a) {
    std::cout << a << std::endl;
}


int main() {
    int a = 10;
    //std::cref(a) amd a is both ok
    print(std::cref(a));
    return 0;
}
