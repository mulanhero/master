#include <iostream>
#include <functional>
#include <iterator>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 4, 5, 6};
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));

    std::cout << std::endl;
    auto pos1 = find_if(vec.begin(), vec.end(), std::bind2nd(std::greater<int>(), 3));
    std::cout << *pos1 << std::endl;
    
    auto pos2 = find_if(vec.rbegin(), vec.rend(), std::not1(std::bind2nd(std::greater<int>(), 3)));
    std::cout << *pos2 << std::endl;
    return 0;
}
