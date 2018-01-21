#include <iostream>
#include <string>
#include <boost/algorithm/string/erase.hpp>


int main() {

    const std::string str = "Hello, hello, my dear reader.";

    std::cout << "orig: " << str << std::endl;
    std::cout << "boost::algorithm::erase_all_copy: " << boost::algorithm::erase_all_copy(str, ",") << std::endl;
    std::cout << "boost::algorithm::erase_first_copy: " << boost::algorithm::erase_first_copy(str, ",") << std::endl;
    std::cout << "boost::algorithm::erase_last_copy: " << boost::algorithm::erase_last_copy(str, ",") << std::endl;
    std::cout << "boost::algorithm::erase_nth_copy: " << boost::algorithm::erase_nth_copy(str, ",", 1) << std::endl;
    
    std::cout << "boost::algorithm::ierase_all_copy: " << boost::algorithm::ierase_all_copy(str, "hello") << std::endl;
    return 0;
}
