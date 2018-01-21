#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <boost/lexical_cast.hpp>

int main() {

    double pi = 3.1415926;
    std::string pi_str;
    pi_str = boost::lexical_cast<std::string>(pi);
    std::cout << pi_str << std::endl;

    return 0;
}
