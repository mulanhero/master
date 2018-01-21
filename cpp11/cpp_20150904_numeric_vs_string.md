#string与数值变换

##1 `to_string()` vs. `boost::lexical_cast()`
###1.1 to_string()
cpp11提供了`to_string()`能够把数值转换为`std::string`.  

	double d = 3.1415926;
    std::string s = std::to_string(d); //std::to_string()
    std::cout << s << std::endl;

###1.2 to_string()示例
boost提供了`boost::lexical_cast()`能够方便把std::string转为数值。

	#include <boost/lexical_cast.hpp>
	#include <iostream>
	
	void test() {
	    std::string s = "3.1415";
	    float v = boost::lexical_cast<float>(s);
	    std::cout << v << std::endl;
	}


##2 自定义一个toString/fromString工具

###2.1 基于template函数和stringstream
	
	#include <sstream>

	template <class T>
	inline bool fromString(const std::string& str, T& tx) {
	    std::stringstream ss(str);
	    return (ss >> tx) ? true : false;
	}
	
	void test_with_std_to_string() {
	    double d = 3.1415926;
	    std::string s = std::to_string(d); //std::to_string()
	    std::cout << s << std::endl;
	}
 
###2.2 测试
	
	double pi = 3.1415;
    std::string str = toString(pi);
    std::cout << str << std::endl;

    std::string estr = "5e-4";
    float ef;
    if (fromString(estr, ef)) {
        std::cout << ef << std::endl;
    } else {
        std::cout << "error string format" << std::endl; 
    }