#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>


int main() {
    std::vector<int> i_vec = {2, 34, 5, 22, 55, 1, 9, 88};
    for (auto& i : i_vec) {
        std::cout << i << " ";
    } 
    std::cout << std::endl;
    

    std::sort(i_vec.begin(), i_vec.end(), std::greater<int>());
    for (auto& i : i_vec) {
        std::cout << i << " ";
    } 
    std::cout << std::endl;

    return 0;
}
