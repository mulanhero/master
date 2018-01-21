#hardware_concurrency
##示例

	#include <iostream>
	#include <thread>
	
	int main() {
	    std::cout << std::thread::hardware_concurrency() << std::endl;
	}