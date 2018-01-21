#  srand rand
##0 背景
srand需要种下一个seed，一般用time(NULL)。

##1 举例
	
	#include <iostream>
	#include <algorithm>
	#include <cstdlib>
	#include <iterator>
	
	int rand_number() {
	    return rand() % 100;
	}
	
	struct Uniq_number {
	    int num;
	    Uniq_number() {
	        num = 0;
	    }
	
	    int operator()() {
	        return num++;
	    }
	};	
	
	int main() {
	    srand(time(nullptr));
	
	    std::vector<int> vec(8);
	
	    std::generate(vec.begin(), vec.end(), rand_number);
	    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	    std::cout << std::endl;
	
	    std::generate(vec.begin(), vec.end(), Uniq_number());
	    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	
	    return 0;
	} 