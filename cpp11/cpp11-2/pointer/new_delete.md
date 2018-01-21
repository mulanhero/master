#内存管理
##new/delete和malloc/free的区别是什么？
**new/delete** 除了分配/释放内存，还会调用构造/析构函数

##new/delete和一维数组
	const size_t SIZE = 50;
	Person* p_array = new Person[SIZE];
	...
	delete [] p_array;
	p_array = nullptr;

**Note!!!:** 情非得已，建议使用`vector<Person>`

**Note!!!:**在使用了delete之后，建议把指针指向nullptr，这样可以避免两次重复delete指针或者使用无效的指针。注意：在nullptr上delete是允许的，只是没有任何效果！

##new/delete和二维数组
	
	#include <iostream>
	#include <algorithm>
	int main() {
	    const size_t LEVEL = 3;
	    const size_t SIZE = 5;
	    std::string** cities = new std::string*[LEVEL];
	    for (size_t i = 0; i < LEVEL; ++i) {
	        cities[i] = new std::string[SIZE];
	        for (size_t j = 0; j < SIZE; ++j) {
	            cities[i][j] = "city_"+std::to_string(i)+"_"+std::to_string(j);
	        }
	    }
	
	    for (size_t i = 0; i < LEVEL; ++i) {
	        for (size_t j = 0; j < SIZE; ++j) {
	            std::cout << cities[i][j] << std::endl;
	        }
	    }
	
	
	    for (size_t i = 0; i < LEVEL; ++i) {
	        delete [] cities[i];
	    };
	    delete []  cities;
	}
	
**Note!!!:** 情非得已，尽量用`vector<vector<string>>` 

##箴言
* 尽可能避免使用c风格的字符串和数据，而多用std::string和vector
* 尽可能少用c风格的指针，而多用智能指针`shared_ptr`和`unique_ptr`