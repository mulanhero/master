#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int my_func(int x, int y) {
    return x + 2 * y;
}


class MyClass {
public:
    int operator()(int x, int y) {
        return x + 3 * y;
    }
};

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> vec(array, array + sizeof(array) / sizeof(array[0]));

    int init = 100;

    int acc_result = std::accumulate(vec.begin(), vec.end(), init);
    std::cout << "acc_result:" << acc_result << std::endl;

    int minus_result = std::accumulate(vec.begin(), vec.end(), init, std::minus<int>());
    std::cout << "minus_result:" << minus_result << std::endl;

    int my_func_result = std::accumulate(vec.begin(), vec.end(), init, my_func);
    std::cout << "my_func_result:" << my_func_result << std::endl; 


    MyClass my_class;
    int my_class_result = std::accumulate(vec.begin(), vec.end(), init, my_class);
    std::cout << "my_class_result :" << my_class_result << std::endl;


    return 0;
}
