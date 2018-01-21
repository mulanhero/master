#include <array>
#include <iostream>

int main() {
    std::array<int, 3> my_array =  {7,8,9};
    std::cout << my_array.size() << std::endl;
    for (auto& i : my_array) {
        std::cout << i << std::endl;
    }
    return 0;
}
