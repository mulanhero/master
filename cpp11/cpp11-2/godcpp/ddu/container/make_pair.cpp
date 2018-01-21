#include <utility>
#include <functional>
#include <iostream>

int main() {
    int i = 0;
    int array[] = {1, 2, 3, 4, 5};

    auto p1 = std::make_pair(i, array[1]);
    std::cout << p1.first << "," << p1.second << std::endl;

    std::pair<int&, int*> p2 = std::make_pair(std::ref(i), array);
    i = 9;
    std::cout << p2.first << "," << p2.second[3] << std::endl;
   return 0;
}
