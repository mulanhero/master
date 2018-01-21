#include <iostream>
#include <string>
#include <boost/regex.hpp>

int main() {

    boost::regex::flag_type flag = boost::regex::extended
        | boost::regex::icase
        | boost::regex::no_except;
    const static std::string re = "(\\d)(\\d)";

    const boost::regex e(re, flag);
    if(e.status()) {
        std::cout << "incorrect regex pattern" << std::endl;
        return -1;
    }

    std::string str = "12";

    std::string replace_re = "$2:$1";
    std::string replaced_str = boost::regex_replace(str, e, replace_re);
    std::cout << replaced_str << std::endl;

    return 0;
}
