#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>

const int SIZE = 5;

std::unique_ptr<int> make_int_ptr(int n) {
    return std::unique_ptr<int>(new int(n));
}

void show(std::unique_ptr<int>& int_ptr_ref) {
    std::cout << *int_ptr_ref << std::endl;
}

int main() {
    std::shared_ptr<int> sp(make_int_ptr(4));
    return 0;
}
