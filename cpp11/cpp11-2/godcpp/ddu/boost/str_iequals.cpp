#include <iostream>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <algorithm>
#include <string>

int main() {
    std::string str1 = "heLLo";
    std::string str2 = "HEllo";
    //1. boost::iequals
    std::cout << boost::iequals(str1, str2) << std::endl;

    //2. boost::is_iequal
    std::cout << ( (str1.size() == str2.size()) 
        && std::equal(str1.begin(), str1.end(), 
               str2.begin(), boost::is_iequal()) ) << std::endl;
    //3.boost::to_lower_copy
    std::string str1_low = boost::to_lower_copy(str1);
    std::string str2_low = boost::to_lower_copy(str2);
    std::cout << (str1_low == str2_low) << std::endl;

    //4. boost::to_uppper_copy
    std::string str1_up = boost::to_upper_copy(str1);
    std::string str2_up = boost::to_upper_copy(str2);
    std::cout << (str1_up == str2_up) << std::endl;

    //5.boost::to_lower
    boost::to_lower(str1);
    boost::to_lower(str2);
    std::cout << str1 << ", " << str2 << std::endl;
    std::cout << (str1 == str2) << std::endl;

    return 0;
}
