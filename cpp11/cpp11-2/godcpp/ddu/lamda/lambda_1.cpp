#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
void print_id(int i) {
    std::cout << i << ":";
}
int main () {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::for_each(vec.begin(), vec.end(), print_id);
    std::cout << std::endl;

    std::for_each(vec.begin(), vec.end(), [](int i) {std::cout << i << ":";});
    std::cout << std::endl;

    return 0;
}
