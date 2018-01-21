#include <iostream>
#include <sstream>

template <class T>
T convert(std::string& str) {
    T val;

    if (str.empty()) {
        std::cerr << "str is empty" << std::endl;
        exit(-1);
    }
    std::stringstream ss(str);
    ss >> val;
    
    if (ss.fail()) {
        std::cerr << "failed to >> in stringstream "<< std::endl;
        exit(-1);
    }

    return val;
}

int main() {
    std::string str = "123";
    int value = convert<int>(str);
    if (value == 123) {
        std::cout << "val == 123" << std::endl;
    }

    std::string str2;
    float f2 = convert<float>(str2);
}
