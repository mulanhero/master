#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <ctype.h>

int main() {
    std::string str = "hello";
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    std::cout << str << std::endl;
    return 0;
}
