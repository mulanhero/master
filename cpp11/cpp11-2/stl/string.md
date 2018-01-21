#string
##背景
##ss
## 示例
###eg1

把node[1-10].any.com解析成为node1.any.com,node2.any.com,等等。

	#include <iostream>
	#include <string>
	#include <vector>
	#include <algorithm>
	#include <iterator>
	#include <sstream>
	int main() {
	    typedef std::string::size_type SIZE_T;
	    std::string hosts = "node[1-10].any.com";
	    std::vector<std::string> vec;
	
	    SIZE_T left = hosts.find("[");
	    SIZE_T dash = hosts.find("-");
	    SIZE_T right = hosts.find(']');
	
	    std::string prefix = hosts.substr(0, left-0);
	    std::string postfix = hosts.substr(right+1);
	
	    int start = std::stoi(hosts.substr(left+1, dash-left-1));
	    int end = std::stoi(hosts.substr(dash+1, right-dash-1));
	
	    while (start <= end) {
	        std::stringstream ss;
	        ss << prefix << start << postfix;
	        vec.push_back(ss.str());
	        ++start;
	    }
	
	    std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	
	    return 0;
	}

###eg2
输入一行，把单词翻转输出。

	#include <iostream>
	#include <string>
	#include <vector>
	#include <algorithm>
	#include <iterator>
	
	int main() {
	    typedef std::string::size_type SIZE_T;
	    std::string delims = " \t.,;";
	    std::string line;
	    while (std::getline(std::cin, line)) {
	       SIZE_T start = line.find_first_not_of(delims); 
	       while (start != std::string::npos) {
	           SIZE_T end = line.find_first_of(delims, start);
	           std::string word = line.substr(start, end-start);
	           std::reverse(word.begin(), word.end()); 
	           std::cout << word << std::endl;
	           start = line.find_first_not_of(delims, end);
	       }
	    }
	    return 0;
	}