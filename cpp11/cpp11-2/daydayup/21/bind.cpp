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


std::string concat(std::string& str1, std::string& str2) {
    return str1 + " " + str2;
}

class MyClass {
    public:
        std::string concat(std::string& str1, std::string& str2) {
            return str1 + " " + str2;
        }
};

int main() {
    std::string first_name = "jimmy";
    std::string family_name = "cao";

    auto bind_func1 = std::bind(concat, first_name, std::placeholders::_1);
    std::cout << bind_func1(family_name) << std::endl;

    auto bind_func2 = std::bind(concat, std::placeholders::_1, std::placeholders::_2);
    std::cout<< bind_func2(first_name, family_name) << std::endl;

    MyClass my;
    auto bind_func3 = std::bind(&MyClass::concat, my, std::placeholders::_1, family_name);
    std::cout << bind_func3(first_name) << std::endl;
    return 0;
}
