#include <iostream>
#include <boost/format.hpp>
#include <string>

int main() {
    std::string city = "shanghai";
    int postcode = 201203;
    std::string con = (boost::format("%s_%d")%city%postcode).str();
    std::cout << con << std::endl;

    return 0;
}
