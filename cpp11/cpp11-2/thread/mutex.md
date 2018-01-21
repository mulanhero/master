	#include <iostream>
	#include <vector>
	#include <thread>
	#include <mutex>
	#include <unistd.h>
	
	int main() {
	    std::vector<std::thread::id> ids;
	    std::vector<std::thread::id> ids2;
	    int num_threads = 10;
	    std::mutex mtx;
	    std::vector<std::thread> threads; 
	    for (int i = 0; i < num_threads; ++i) {
	        threads.push_back(std::thread([&](){
	                    srand(time(NULL));
	                    for (int j = 0; j < 10; ++j) {
	                        mtx.lock();
	                        ids.push_back(std::this_thread::get_id());
	                        mtx.unlock();
	                        usleep(rand()%1000);
	                    } 
	
	                    for (int j = 0; j < 10; ++j) {
	                        std::unique_lock<std::mutex> lock(mtx);
	                        ids2.push_back(std::this_thread::get_id());
	                    }
	                    }));
	    }
	
	    for (auto& t : threads) {
	        t.join();
	    }
	//    std::cout << "size:" << ids.size() << std::endl;
	    for (auto& id : ids) {
	        std::cout << "id:" << id << std::endl;
	    }
	    for (auto& id : ids2) {
	        std::cout << "id:" << id << std::endl;
	    }
	    return 0;
	}
