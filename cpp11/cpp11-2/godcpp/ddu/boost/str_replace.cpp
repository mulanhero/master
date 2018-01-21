#include <iostream>
#include <string>
#include <boost/algorithm/string/replace.hpp>

int main() {
    const std::string str = "Hello, hello, my dear reader.";
    std::cout << "orig: " << str << std::endl;

    std::cout << "boost::algorithm::replace_all_copy: " << boost::algorithm::replace_all_copy(str, ",", "!") << std::endl;
    std::cout << "boost::algorithm::replace_first_copy: " << boost::algorithm::replace_first_copy(str, ",", "!") << std::endl;
    std::cout << "boost::algorithm::replace_last_copy: " << boost::algorithm::replace_last_copy(str, ",", "!") << std::endl;
    std::cout << "boost::algorithm::replace_nth_copy: " << boost::algorithm::replace_nth_copy(str, ",", 1, "!") << std::endl; 
    std::cout << "boost::algorithm::ireplace_all_copy: " << boost::algorithm::ireplace_all_copy(str, "hello", "hi") << std::endl;

    std::cout << "boost::algorithm::replace_head_copy: " << boost::algorithm::replace_head_copy(str, 5, "haha") << std::endl;
    return 0;
}
