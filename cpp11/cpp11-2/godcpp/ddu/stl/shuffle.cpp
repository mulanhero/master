#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

int main() {

    std::vector<std::string> str_vec = {"shanghai", "bejing", "xian", "shenzhen"};
    for (auto& str : str_vec) {
        std::cout << str << std::endl;
    }
    auto engine = std::default_random_engine();
    std::shuffle(str_vec.begin(), str_vec.end(), engine);
    std::cout << "------------after shuffle-------" << std::endl;
    for (auto& str : str_vec) {
        std::cout << str << std::endl;
    }
    return 0;
}
