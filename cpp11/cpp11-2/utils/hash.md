#hash

##`boost::hash<T>`

	#include <iostream>
	#include <boost/functional/hash.hpp>
	
	int main() {
	    boost::hash<std::string> str_hash;
	    std::size_t h_result = str_hash("beijing");
	    std::cout << "h_result:" << h_result << std::endl;
	    return 0;
	}