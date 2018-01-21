#cpp11 thread

##0 背景
cpp11引入了标准的线程库，解决跨平台问题。

##1

###1.1 thread_func

	#include <iostream>
	#include <thread>
	
	void acc(int id, int num_iter) {
	    for (int i = 0; i < num_iter; ++i) {
	        std::cout << "id:" << id << ", num_iter:" << i << std::endl;
	    }
	}
	
	int main() {
	    std::cout.sync_with_stdio(true);
	    std::thread t1(acc, 1, 4);
	    std::thread t2(acc, 2, 5);
	
	    t1.join();
	    t2.join();
	    return 0;
	}

###1.2 `thread_functor`

	#include <thread>
	#include <iostream>
	
	class FunctorClass {
	public:
	    FunctorClass(int id, int value) : _id(id), _value(value) {}
	
	    void operator()(){
	        std::cout << "id:" << _id << ", value:" << _value << std::endl;
	    }
	
	private:
	    int _id;
	    int _value;
	};
	
	int main() {
	    //by {}
	    std::thread t1{FunctorClass(1, 1)};
	    t1.join();
	
	    //by()
	    std::thread t2(FunctorClass(2,2));
	    t2.join();
	
	    //by object
	    FunctorClass obj(3,3);
	    std::thread t3(obj);
	    t3.join();
	    return 0;
	}

###1.3 `thread_lambda`

	#include <thread>
	#include <iostream>
	
	
	int main() {
	    int id = 1;
	    int num_iter = 3;
	    std::thread t1 = std::thread([id, num_iter](){
	                for (int i = 0; i < num_iter; ++i) {
	                    std::cout << "id:" << id << ", i:" << i << std::endl;
	                }
	            });
	    t1.join();
	    return 0;
	}

下一个：

	#include <iostream>
	#include <thread>
	
	class Test {
	public:
	    Test(int sum=0) : _sum(sum) {
	    }
	
	    void run(int start, int end) {
	        std::thread t = std::thread([this, start, end](){
	            int tmp = start;
	            while (tmp < end) {
	                _sum += tmp;
	                ++tmp;
	            }
	        }); 
	        t.join();
	    }
	
	    void print() {
	        std::cout << "_sum:" << _sum << std::endl; 
	    }
	private:
	    int _sum;
	};
	
	int main() {
	    Test t(100);
	    t.run(1, 9);
	    t.print();
	    return 0;
	}

###1.4 `thread_member_func`

	#include <iostream>
	#include <thread>
	
	
	class MyClass {
	public:
	    MyClass(int value) : _value(value) {}
	
	    void process(int other) {
	        std::cout << "value+other:" << _value + other << std::endl;
	    }
	
	private:
	    int _value;
	};
	
	int main() {
	    MyClass my(1);
	   // std::thread t1 = std::thread(&MyClass::process, my);
	    std::thread t1 = std::thread(&MyClass::process, &my, 9);
	    t1.join();
	    return 0;
	}