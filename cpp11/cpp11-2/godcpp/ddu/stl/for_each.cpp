#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

void my_func(std::string& str) {
   str.append("s");
}

class Postfix {
public:
    void operator() (std::string& str) {
        str.append("ing");
    }
};
int main() {
    std::vector<std::string> vec = {"bee", "pig", "apple"};

    std::for_each(vec.begin(), vec.end(), my_func);
    for (auto& s : vec) {
        std::cout << s << " ";
    }
    std::cout << std::endl;

    std::for_each(vec.begin(), vec.end(), Postfix());
    for (auto& s : vec) {
        std::cout << s << " ";
    }
    std::cout << std::endl;


    return 0;
}
