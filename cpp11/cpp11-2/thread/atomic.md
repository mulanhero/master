#atomic
##0 背景
##1 示例
### eg1 `feach_add()`

	#include <iostream>
	#include <thread>
	#include <atomic>
	
	int main() {
	    std::atomic<int> value(0);
	
	    int fetched_value = value.fetch_add(4);
	    std::cout << "fetched_value :" << fetched_value << std::endl;
	    std::cout << "value :" << value << std::endl;
	    return 0;
	}


###eg2 `atomic_store()_load()`

	#include "zall.h"

	void set(std::atomic<int>& value) {
	    std::this_thread::sleep_for(std::chrono::milliseconds(5));
	    value.store(5);
	}
	
	
	int main() {
	    std::atomic<int> value(0);
	    std::thread t = std::thread(set, std::ref(value));
	
	    while(value.load() == 0) {
	        std::cout << "not ready yet" << std::endl;
	        std::this_thread::yield();
	    }
	    std::cout << value << std::endl;
	    t.join();
	    return 0;
	}

###eg3

	#include <vector>
	#include <string>
	#include <sstream>
	#include <algorithm>
	#include <iterator>
	#include <fstream>
	#include <iomanip>
	#include <thread>
	#include <boost/lexical_cast.hpp>
	#include <functional>
	#include <atomic>
	#include <chrono>
	
	
	void add(std::atomic<int>& value) {
	    for (int i = 1; i <= 10; i++) {
	        ++value;
	        std::this_thread::sleep_for(std::chrono::milliseconds(1));
	    }
	}
	
	
	int main() {
	    std::atomic<int> value(0);
	    //int value(0);
	
	    std::vector<std::thread> t_vec;
	    for (int i = 1; i <= 10; i++) {
	//        t_vec.push_back(std::thread(add, std::ref(value)));
	
	
	/*
	        t_vec.push_back(std::thread([&](){
	                      for (int i = 1; i <= 10; i++) {
	                        ++value;
	                      }
	                    })
	                );
	*/
	        t_vec.emplace_back([&](){
	                    for (int i = 1; i <= 10; i++) {
	                        ++value;
	                    }
	                });
	    }
	
	    for (auto& t : t_vec) {
	        t.join();
	    }
	
	    std::cout << "value:" << value << std::endl;
	    return 0;
	}