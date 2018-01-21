#include <iostream>
#include <functional>
#include <vector>

int main() {
    [](int i) { std::cout << i << std::endl;} (42);

    auto func = [](int i) { std::cout << i << std::endl;};
    func(42);
    return 0;
}
