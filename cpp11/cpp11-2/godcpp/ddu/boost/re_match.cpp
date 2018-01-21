#include <iostream>
#include <string>
#include <boost/regex.hpp>

int main() {
    boost::regex::flag_type flag = boost::regex::extended 
        | boost::regex::icase 
        | boost::regex::no_except;
    std::string regex = "(\\d{3}[#-]){2}";
    const boost::regex e(regex, flag);
    if (e.status()) {
        std::cout << "incorrect regex pattern!" << std::endl;
        exit(-1);
    }
    
    std::string test_str = "123#123-";
    
    //boost::regex_match
    bool matched = boost::regex_match(test_str, e);
    if (matched) {
        std::cout << "matched" << std::endl;
    } else {
        std::cout << "not matched.." << std::endl;
    }

    //2. boost::regex_search
    boost::smatch results;
    bool matched2 = boost::regex_search(test_str, results, e);
    if (matched2) {
        std::cout << "matched" << std::endl;
        std::copy(results.begin(), results.end(), 
                std::ostream_iterator<std::string>(std::cout, ",\n"));
        std::cout << std::endl;
    }
    

    
    return 0;
}
