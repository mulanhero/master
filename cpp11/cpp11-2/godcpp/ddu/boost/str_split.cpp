#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <vector>

int main() {
    std::string str = "Hello, hello, my dear reader. Thanks very much!";
    
    std::vector<std::string> tmp_records;
    //1. boost::split
    boost::split(tmp_records, str, boost::is_any_of(",.!"), boost::token_compress_on);

    for (auto& item : tmp_records) {
        std::cout << item << std::endl;
    }


    //2. boost::make_split_iterator
    std::string str2 = "Hello, hello, my dear reader. Thanks very much!";
    auto split_it = boost::make_split_iterator(str2, 
            boost::algorithm::token_finder(boost::is_any_of(",.!")));
    for (size_t i = 1; !split_it.eof(); ++split_it, ++i) {
        std::cout << i << ":" << *split_it << std::endl;
        size_t count = std::count(split_it->begin(), split_it->end(), ' ');
        std::cout << i << ": size: " << split_it->size() << ": blank count:" << count << std::endl; 
    }
    return 0;
}
