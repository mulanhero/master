#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <sstream>


template<class T>
std::string join1(std::vector<T>& vec, std::string& delims) {
    std::string tmp = "";
    for (auto it = vec.begin(); it != (vec.end()-1); ++it) {
        tmp.append(boost::lexical_cast<std::string>(*it)).append(delims);
    } 
    tmp.append(boost::lexical_cast<std::string>(*(vec.end()-1)));
    return std::move(tmp);
}


template<class T>
std::string join2(std::vector<T>& vec, std::string& delims) {
    std::stringstream ss;
    for (auto it = vec.begin(); it != (vec.end()-1); ++it) {
        ss << *it << delims;
    }
    ss << *(vec.end()-1);
    return std::move(ss.str());
} 


int main() {
    std::vector<std::string> vec = {"shanghai", "beijing", "shenzhen"};
    std::string delims = ":";

    std::string result = join1(vec, delims);
    std::cout << result << std::endl;
    
    std::string result2 = join2(vec, delims);
    std::cout << result2 << std::endl;
    return 0;
}
