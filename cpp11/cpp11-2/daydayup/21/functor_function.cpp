#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <thread>
#include <boost/lexical_cast.hpp>
#include <functional>
typedef std::function<int(int, int)> Func;

int add(int a, int b) {
    return a + b;
}

class Multiply {
public:
    int operator()(int a, int b) {
        return a * b;
    }
};


int main() {
    Func func1 = add;
    std::cout << func1(2, 3) << std::endl;

    Func func2 = Multiply();
    std::cout << func2(2, 3) << std::endl;
    return 0;
}
