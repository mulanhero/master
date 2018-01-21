#include <tuple>
#include <iostream>
#include <string>

int main() {
    std::tuple<int, char, std::string> my_tuple(11, 'A', "jimmy");
    std::cout << std::get<0>(my_tuple) << std::endl;
    std::cout << std::get<1>(my_tuple) << std::endl;
    std::get<2>(my_tuple) = "amao";
    std::cout << std::get<2>(my_tuple) << std::endl;


    std::tuple<int, char, std::string> your_tuple = std::make_tuple(35, 'B', "Cool");
    std::cout << std::get<0>(your_tuple) << std::endl;
    
    return 0;
}
