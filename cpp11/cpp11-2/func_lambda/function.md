#函数
##auto 函数
	
	#include <iostream>
	#include <vector>
	#include <string>
	#include <algorithm>
	#include <memory>
	auto get_vec_s_ptr(std::size_t size) -> std::shared_ptr<std::vector<std::string>> {
	    std::vector<std::string> vec = {"beijing", "shanghai", "shenzhen"}; 
	    std::shared_ptr<std::vector<std::string> > vec_s_ptr = std::make_shared<std::vector<std::string> >(size);
	    std::copy(vec.begin(), vec.end(), vec_s_ptr->begin());
	    return vec_s_ptr;
	}
	
	
	int main() {
	    std::size_t size = 3;
	    std::shared_ptr<std::vector<std::string>> result_ptr = get_vec_s_ptr(size);
	    for (auto it = result_ptr->begin(); it != result_ptr->end(); ++it) {
	        std::cout << *it << std::endl; 
	    }
	    return 0; 
	}

##