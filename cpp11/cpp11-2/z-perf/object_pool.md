#对象池
##0 背景
cache、object pool、thread pool是高性能编程的三大法宝。当需要频繁为某类构建对象、释放对象时，如果能够通过object pool来hold住这些对象，当需要的时候直接从pool中取，释放的时候还给pool，这样的话，就可以大大提高性能。

##1 实现示例1
以下实现了一个简单的object pool，需要用户类具有default constructor。

	#include <mutex>
	#include <thread>
	#include <queue>

	template <class T>
	class ObjectPool {
	public:
	    ObjectPool(size_t chunk_size = DEFAULT_CHUNK_SIZE) : _chunk_size(chunk_size) { 
	        CHECK(chunk_size > 0);
	        _alloc_chunk();
	    }
	
	    ObjectPool(const ObjectPool<T>& other) = delete;
	    ObjectPool<T>& operator=(const ObjectPool<T>& rhs) = delete;
	
	    std::shared_ptr<T> acquire() {
	        std::unique_lock<std::recursive_mutex> lock(_mutex);
	        if (_freed_objects.empty()) {
	            _alloc_chunk();
	        }
	        auto obj = _freed_objects.front();
	        _freed_objects.pop();
	        return obj;
	    }
	
	    void release(std::shared_ptr<T> obj) {
	        std::unique_lock<std::recursive_mutex> lock(_mutex);
	        _freed_objects.push(obj);
	    }
	
	    size_t freed_size() {
	        std::unique_lock<std::recursive_mutex> lock(_mutex);
	        return _freed_objects.size();
	    }
	private:
	    void _alloc_chunk() {
	        std::unique_lock<std::recursive_mutex> lock(_mutex);
	        for (size_t i  = 0; i < _chunk_size; ++i) {
	            _freed_objects.push(std::make_shared<T>());
	        }
	    }
	
	    size_t _chunk_size;
	    static const size_t DEFAULT_CHUNK_SIZE = 10;
	    std::queue<std::shared_ptr<T>> _freed_objects;
	    std::recursive_mutex _mutex;
	};

测试代码：

	#include "object_pool.h"

	class Person {
	public:
	    Person() = default;
	    Person(std::string id, std::string name) : _id(id), _name(name) {
	    }
	
	    std::string id() {
	        return _id;
	    }
	
	    void set_id(std::string id) {
	        _id = id;
	    }
	
	    std::string name() {
	        return _name;
	    }
	
	    void set_name(std::string name){
	        _name = name;
	    }
	
	    friend ostream& operator<< (std::ostream& out, const Person& p) {
	        out << "id:" << p._id << ", name:" << p._name;
	        return out;  
	    }
	private:
	    std::string _id;
	    std::string _name;
	};
	
	TEST(ObjectPoolTestSuite, object_pool_test) {
	    size_t chunk_size = 100;
	    ObjectPool<Person> pool(chunk_size);
	   
	    
	    size_t thread_size = 2; 
	    int id = 0; 
	    std::vector<std::thread> threads;
	    threads.reserve(thread_size);
	
	    for (size_t i = 0; i < thread_size; ++i) {
	        threads.push_back(std::thread([&]() {
	            std::shared_ptr<Person> p1 = pool.acquire();
	            p1->set_id(std::to_string(id));
	            p1->set_name(std::to_string(id++));
	            std::cout << *p1 << std::endl;
	
	            std::cout << "thread_id:" << std::this_thread::get_id() 
	                << ",freed_size:" << pool.freed_size()
	                << std::endl;
	            pool.release(p1);
	        }));
	    }
	 
	    for (auto& th: threads) {
	        std::cout << "thread_id:" << std::this_thread::get_id();
	        th.join();
	    }
	
	    EXPECT_EQ(chunk_size, pool.freed_size());
	}
	
	int main(int argc, char* argv[]) {
	    testing::InitGoogleTest(&argc, argv);
	    return RUN_ALL_TESTS();
	}

	
以上实现是通过
Object Pool