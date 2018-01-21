#include <iostream>
#include <cstdint>
#include <string>

template <class Type>
int transform(Type t) {
    return sizeof(t);
}

int main() {
    long a = 1;

    std::cout << transform(a) << std::endl;
    uint64_t b = 2;
    std::cout << transform(b) << std::endl;
    return 0;
}
