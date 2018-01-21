#include <string>
#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

void sub_str() {
	std::string str_orig = "hello, world!";
	char o_ch = str_orig.c_str()[4];
	std::string llo_str = str_orig.substr(2, 3); //length
	std::cout << o_ch << std::endl;
	std::cout << llo_str << std::endl;
}

void find_str() {
	std::string str_orig = "hello, world!";
	std::string to_find = "wo";
	if (str_orig.find(to_find, 5) != std::string::npos) {
		std::cout << "found" << std::endl;
	}
}

void concat() {
	std::string first = "hello,";
	std::string second = "world!";
	std::string result = first + " " + second;
	std::cout << result << std::endl;
}

void replace() {
	std::string str_orig = "hello, world!";
	std::string to_replace = "hello";
	if (str_orig.find(to_replace) != std::string::npos) {
		str_orig.replace(str_orig.find(to_replace), to_replace.length(), "hi");
	}

	std::cout << str_orig << std::endl;
}

void to_string_to_float() {
	float pi = 3.1415;
	std::string pi_str = std::to_string(pi);
	std::cout << pi_str << std::endl;
	
	float pi2 = atof(pi_str.c_str());
	std::cout << "area(2):" << pi2 * 2 * 2 << std::endl;
	//with boost::lexical_cast
	float pi3 = boost::lexical_cast<float>(pi_str);
	std::cout << "area(2):" << pi3 * 2 * 2 << std::endl;
	//std::stof
	float pi4 = std::stof(pi_str);
	std::cout << "area(2):" << pi4 * 2 * 2 << std::endl;
}

void str_len() {
	std::string str = "hello, world!";	
	std::cout << str.length() << std::endl;
}

void str_split() {
	std::string str_orig = "123,456,789";
	std::vector<std::string> items;
	boost::split(items, str_orig, boost::is_any_of(","));
	int result = 0;
	for (auto item : items) {
		result += atoi(item.c_str());
	}
	std::cout << "result:" << result << std::endl;
}

void str_compare() {
	std::string str1 = "hello, world!";
	if (str1 == "hello, world!") {
		std::cout << "==" << std::endl;
	}
}

void str_reverse() {
	std::string str = "12345";
	std::reverse(str.begin(), str.end());
	std::cout << "after reverse, str:" << str << std::endl;
}

int main() {
	sub_str();	
	find_str();
	concat();
	replace();
	to_string_to_float();
	str_len();
	str_split();
	str_compare();
	str_reverse();
	return 0;
}
