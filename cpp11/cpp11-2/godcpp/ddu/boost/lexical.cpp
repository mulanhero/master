#include <iostream>
#include <boost/lexical_cast.hpp>

int main() {
    using boost::lexical_cast;
    int i = lexical_cast<int>("123");
    double d = lexical_cast<int>("123.12");
    std::cout << i << std::endl;
    std::cout << d << std::endl;
    
    return 0;
}
