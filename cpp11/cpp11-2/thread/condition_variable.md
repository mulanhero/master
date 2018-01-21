#condition_variable
#0 背景

#示例
##eg1  `condition_variable, notify_one()`
	#include <iostream>
	#include <thread>
	#include <mutex>
	#include <condition_variable>
	#include <vector>
	
	class Test {
	public:
	    Test() = default;
	    ~Test() {
	        _write_thread.join();
	        _read_thread.join();
	    }
	  
	    void run() {
	        _read_thread = std::thread([this](){
	                std::unique_lock<std::mutex> lock(_mtx);
	                _cv.wait(lock, [this](){return _ready == true;});
	
	                for (auto it : _vec) {
	                    std::cout << it << std::endl;
	                }
	
	                });
	
	        _write_thread = std::thread([this]() {
	                std::unique_lock<std::mutex> lock(_mtx); 
	                    for (int i = 0; i < 10; ++i) {
	                        _vec.push_back(i);
	                    }
	                    _ready = true;
	                    _cv.notify_one();
	                });
	        
	    }
	
	
	private:
	    std::vector<int> _vec;
	    bool _ready = false;
	
	    std::mutex _mtx;
	    std::condition_variable _cv;
	
	    std::thread _write_thread; 
	    std::thread _read_thread;
	};
	
	int main() {
	    Test t;
	    t.run();
	    return 0;
	}

##eg2 `notify_all()`

	#include <iostream>
	#include <thread>
	#include <mutex>
	#include <condition_variable>
	#include <vector>
	
	class Test {
	public:
	    Test(int num) {
	        _read_threads = std::vector<std::thread>(3);
	    }
	
	    ~Test() {
	        for (auto& t : _read_threads) {
	            t.join();
	        }
	        _write_thread.join();
	    }
	  
	    void run() {
	        for (int id = 0; id < _read_threads.size(); ++id) {
	            _read_threads[id] = std::thread([id, this](){ 
	                    std::unique_lock<std::mutex> lock(_mtx);
	                    _cv.wait(lock, [id, this](){return _ready == true;});
	                    for (auto it : _vec) {
	                        std::cout << "id:" << id << ", value:" << it << std::endl;
	                    }
	                });
	        }
	        
	        _write_thread = std::thread([this]() {
	            std::unique_lock<std::mutex> lock(_mtx); 
	            for (int i = 0; i < 10; ++i) {
	                _vec.push_back(i);
	            }
	            _ready = true;
	            _cv.notify_all();
	        }); 
	    } 
	
	private:
	    std::vector<int> _vec;
	    bool _ready = false;
	
	    std::mutex _mtx;
	    std::condition_variable _cv;
	
	    std::thread _write_thread; 
	    std::vector<std::thread> _read_threads;
	};
	
	int main() {
	    int read_thread_num = 3;
	    Test t(read_thread_num);
	    t.run();
	    return 0;
	}

##eg3 `nofity_all() push_back()`
	
	#include <iostream>
	#include <thread>
	#include <mutex>
	#include <condition_variable>
	#include <vector>
	
	class Test {
	public:
	    Test(int read_thread_num) : _read_thread_num(read_thread_num) {
	    }
	
	    ~Test() {
	        for (auto& t : _read_threads) {
	            t.join();
	        }
	        _write_thread.join();
	    }
	  
	    void run() {
	        for (int id = 0; id < _read_thread_num; ++id) {
	            //jimmy:
	            //here, we use push_back std::thread(lamda function) to a std::vector<std::thread> 
	            // it will equals:
	            // _read_threads.emplace_back([](){....});
	            _read_threads.push_back(std::thread([id, this](){ 
	                    std::unique_lock<std::mutex> lock(_mtx);
	                    _cv.wait(lock, [id, this](){return _ready == true;});
	                    for (auto it : _vec) {
	                        std::cout << "id:" << id << ", value:" << it << std::endl;
	                    }
	                }));
	        }
	        
	        _write_thread = std::thread([this]() {
	            std::unique_lock<std::mutex> lock(_mtx); 
	            for (int i = 0; i < 10; ++i) {
	                _vec.push_back(i);
	            }
	            _ready = true;
	            _cv.notify_all();
	        }); 
	    } 
	
	private:
	    std::vector<int> _vec;
	    bool _ready = false;
	
	    std::mutex _mtx;
	    std::condition_variable _cv;
	
	    std::thread _write_thread; 
	    std::vector<std::thread> _read_threads;
	    int _read_thread_num;
	};
	
	int main() {
	    int read_thread_num = 3;
	    Test t(read_thread_num);
	    t.run();
	    return 0;
	}

##eg4 `notify_all() emplace_back()`

	#include <iostream>
	#include <thread>
	#include <mutex>
	#include <condition_variable>
	#include <vector>
	
	class Test {
	public:
	    Test(int read_thread_num) : _read_thread_num(read_thread_num) {
	    }
	
	    ~Test() {
	        for (auto& t : _read_threads) {
	            t.join();
	        }
	        _write_thread.join();
	    }
	  
	    void run() {
	        for (int id = 0; id < _read_thread_num; ++id) {
	            //jimmy:
	            //here, we use emplace_back a lamda function to a std::vector<std::thread>
	            // it will equals:
	            // _read_threads.push_back(std::thread([]().......));
	            _read_threads.emplace_back([id, this](){ 
	                    std::unique_lock<std::mutex> lock(_mtx);
	                    _cv.wait(lock, [id, this](){return _ready == true;});
	                    for (auto it : _vec) {
	                        std::cout << "id:" << id << ", value:" << it << std::endl;
	                    }
	                });
	        }
	        
	        _write_thread = std::thread([this]() {
	            std::unique_lock<std::mutex> lock(_mtx); 
	            for (int i = 0; i < 10; ++i) {
	                _vec.push_back(i);
	            }
	            _ready = true;
	            _cv.notify_all();
	        }); 
	    } 
	
	private:
	    std::vector<int> _vec;
	    bool _ready = false;
	
	    std::mutex _mtx;
	    std::condition_variable _cv;
	
	    std::thread _write_thread; 
	    std::vector<std::thread> _read_threads;
	    int _read_thread_num;
	};
	
	int main() {
	    int read_thread_num = 3;
	    Test t(read_thread_num);
	    t.run();
	    return 0;
	}