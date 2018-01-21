#函数指针

##0 背景
很多情况下，需要把函数作为参数传入另一个函数。因此，函数做形参时，往往需要一个**函数类型**。有多种定义**函数类型** 的方法，比如：typedef，using， `std::function`

##1 typedef

typedef定义函数指针，然后可以作为函数的函数形参类型。
	
	#include <iostream>
	typedef bool (*valid_func) (int a, int b);
	
	int find_first_match(int array1[], int array2[], int size, valid_func func) {
	    int idx = -1;
	    for (int i = 0; i < size; ++i) {
	        if (func(array1[i], array2[i])) {
	            idx = i;
	            break;
	        }
	    }
	    return idx;
	}
	
	bool both_odd(int a, int b) {
	    if (a % 2 == 1 && b % 2 == 1) {
	        return true;
	    } else {
	        return false;
	    }
	}
	
	int main() {
	    int array1[] = {1, 4, 5, 6};
	    int array2[] = {2, 3, 7, 8};
	    int idx = find_first_match(array1, array2, sizeof(array1)/sizeof(array1[0]), both_odd);
	    if (idx != -1) {
	        std::cout << "idx:" << idx << std::endl; 
	    } else {
	        std::cout << "not found" << std::endl;
	    } 
	}

##2 using

using定义函数指针类型是c++提供的一种方法。只需要把

	typedef bool (*valid_func) (int a, int b);

替换成
	
	using valid_func = bool (*) (int a, int b);

即可。

##3 `std::function<return_type(param_type,...)>`

std::function就可以申明需要一个什么类型的函数，无须额外定义函数类型。例如上例，秩序把函数做参数部分修改为：

	int find_first_match(int array1[], int array2[], int size, std::function<bool(int, int)> func)

即可。

###3.1 `function as func's param`

	#include <iostream>
	#include <functional>
	#include <algorithm>
	#include <iterator>
	
	typedef std::function<void(std::string&, std::string&)> Operator_func;  
	
	void batch_add(std::vector<std::string>& str_vec, std::string& postfix, 
	        Operator_func operation) {
	    for (auto& str : str_vec) {
	        operation(str, postfix);
	    }
	}
	
	int main() {
	    std::vector<std::string> cities = {"beijing", "shanghai", "shenzhen", "xian"};
	
	    std::string post = "er";
	    batch_add(cities, post, [](std::string& orig, std::string& postfix){
	            orig.append(".").append(postfix);
	            });
	
	    copy(cities.begin(), cities.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	    return 0;
	}
