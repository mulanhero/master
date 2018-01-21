#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    std::vector<std::string> vec = {"hello", "hi", "hallo"};
    std::sort(vec.begin(), vec.end());
    for (auto& i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::sort(vec.begin(), vec.end(), std::greater<std::string>());
    for (auto& i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
