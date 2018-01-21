#include <iostream>
#include <string>
#include <iterator>
#include <sstream>

#include <boost/algorithm/string.hpp>

void convert_with_boost_split() {
	std::string str_orig = "node[12-15].sth.com";	
	std::vector<std::string> result;

	std::vector<std::string> items;
	boost::split(items, str_orig, boost::is_any_of("[-]"));
	int start = atoi(items[1].c_str());
	int end = atoi(items[2].c_str());
	std::cout << "start:" << start << ", end:" << end << std::endl;
	for (int i = start; i <= end; ++i) {
		result.push_back(items[0] + std::to_string(i) + items[3]);
	}
	
	for (auto& it : result) {
		std::cout << it << std::endl;
	}
}

void convert_with_find_substr() {
	std::string str_orig = "node[12-15].sth.com";
	std::vector<std::string> result;

	size_t left = str_orig.find("[");
	size_t right = str_orig.find("]");
	size_t dash = str_orig.find("-");
	
	std::string prefix = str_orig.substr(0, left);
	std::string postfix = str_orig.substr(right + 1);
	
	int start = atoi(str_orig.substr(left+1, dash-left-1).c_str());
	int end = atoi(str_orig.substr(dash+1, right-dash-1).c_str());
	
	while (start <= end) {
		result.push_back(prefix + std::to_string(start) + postfix);			
		++start;
	}

	for (auto& it : result) {
		std::cout << it << std::endl;
	}
}

void convert_with_find_substr2() {
    typedef std::string::size_type SIZE_T;

    std::string hosts = "node[1-10].sth.com";
    std::vector<std::string> vec;

    SIZE_T left_idx = hosts.find("[");
    SIZE_T right_idx = hosts.find("]");
    SIZE_T dash_idx = hosts.find("-");

    std::string prefix = hosts.substr(0, left_idx);
    std::string postfix = hosts.substr(right_idx + 1);

    int start = std::stoi(hosts.substr(left_idx + 1, dash_idx - left_idx - 1));
    int end = std::stoi(hosts.substr(dash_idx + 1, right_idx - dash_idx - 1));


    while (start <= end) {
        std::string tmp = prefix + std::to_string(start) + postfix;
        vec.push_back(tmp);
        ++start;
    }

    std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(std::cout, " "));
}

int main() {
	convert_with_boost_split();
	convert_with_find_substr();
	convert_with_find_substr2();
}
