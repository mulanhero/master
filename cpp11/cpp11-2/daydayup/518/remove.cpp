#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<int> vec = {1, 2, 3, 1, 2, 3, 1, 2, 3};
    auto end = std::remove(vec.begin(), vec.end(), 3);
    std::cout << vec.size() << std::endl;
    vec.erase(end, vec.end());
    std::cout << vec.size() << std::endl;
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));

}
