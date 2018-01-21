#include <vector>
#include <string>
#include <cstdlib>
#include <cxxabi.h>
#include <iostream>

template <class T>
void swap(std::vector<T>& vec, int64_t i, int64_t j) {
    if (i == j) {
        return ;
    }
    T tmp = std::move(vec[i]);
    vec[i] = std::move(vec[j]);
    vec[j] = std::move(tmp);
}


int main() {
    std::vector<std::string> vec = {"shanghai", "beijing", "wuhan", "xian"};
    for (auto& item : vec) {
        std::cout << item << std::endl;
    }

    std::cout << "-------------" << std::endl;
    swap(vec, 1, 2);
    for (auto& item : vec) {
        std::cout << item << std::endl;
    }

    std::string tname = typeid(int).name();

    std::cout << tname << std::endl;
    int status;
    char* demangled_name = abi::__cxa_demangle(tname.c_str(), NULL, NULL, &status);
    std::cout << demangled_name << std::endl;
    
    return 0;
}
