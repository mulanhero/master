##Object pool with boost lockfree queue

## impl:
	#include <atomic>
	#include <thread>
	#include <mutex>
	#include <queue>
	#include <limits>
	
	#include <boost/lockfree/queue.hpp>

	/*
	 * @class ObjectPool object_pool.h "common/object_pool.h"
	 *
	 * @brief ObjectPool is a pool to manage objects, alleviating from frequently 
	 * allocate/release the memory of object. Two groups of interface are provided:
	 * (1) get_object and return_object are thread-safe and with lock, and 
	 * (2) "*_lockfree" interfaces are provided for efficiency with lock-free. 
	 * Users can choose one of the two groups of interface acoordingly.
	 *
	 * @Param T The type of the object. T should be with default constructor.
	 */
	template <class T>
	class ObjectPool {
	public:
	    ObjectPool() : _in_used(0), _objects_lockfree(std::numeric_limits<short>::max()) {
	    }
	
	    ObjectPool(const ObjectPool<T>& other) = delete;
	    ObjectPool<T>& operator=(const ObjectPool<T>& rhs) = delete;
	
	    ~ObjectPool() {
	        while (!_objects_lockfree.empty()) {
	            T* obj = nullptr;
	            while (!_objects_lockfree.pop(obj)) ;
	            delete obj;
	        }
	    } 
	
	    /* 
	     * @brief get an object from pool
	     * @return the object
	     *
	     */
	    std::shared_ptr<T> get_object() {
	        std::unique_lock<std::mutex> lock(_mutex);
	        if (_objects.empty()) {
	            auto obj = std::make_shared<T>();
	            _in_used++;
	            return obj;
	        }
	
	        auto obj = _objects.front();
	        _objects.pop();
	        _in_used++;
	        return obj;
	    }
	
	    /*
	     * @brief get an object from pool (with lock free for efficiency)
	     * @return the object
	     */
	    T* get_object_lockfree() {
	        if (_objects_lockfree.empty()) {
	            auto obj = new T();
	            _in_used++;
	            return obj;
	        }
	        
	        T* obj;
	        while (!_objects_lockfree.pop(obj)) ;
	        _in_used++;
	        return obj;
	    }
	
	    /*
	     * @brief return the obj to pool
	     * @param the obj to be returned
	     */
	    void return_object(std::shared_ptr<T> obj) {
	        std::unique_lock<std::mutex> lock(_mutex);
	        _objects.push(obj);
	        _in_used--;
	    }
	
	
	    /*
	     * @brief return the obj to pool (with lock-free for efficiency)
	     * @param the obj to be returned
	     */
	    void return_object_lockfree(T* obj) {
	        while (!_objects_lockfree.bounded_push(obj)) ;
	        _in_used--;
	    }
	    
	
	    /*
	     * @brief get the number of objects in used 
	     * @return the number of objects in used 
	     */
	    size_t in_used() const {
	        return _in_used.load();
	    }
	
	private:
	    std::atomic<size_t> _in_used;
	
	    std::queue<std::shared_ptr<T>> _objects;
	    std::mutex _mutex;
	
	    boost::lockfree::queue<T*> _objects_lockfree;
	};
	
##test
	
	#include <iostream>
	#include <glog/logging.h>
	#include <gtest/gtest.h>
	
	#include "common/object_pool.h"
	
	#include <thread>
	#include <atomic>
	#include <chrono>
	
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
	    ObjectPool<Person> pool;
	   
	    
	    size_t thread_size = 20; 
	    std::atomic<size_t> id(0); 
	    std::vector<std::thread> threads;
	    threads.reserve(thread_size);
	
	    for (size_t i = 0; i < thread_size; ++i) {
	        threads.push_back(std::thread([&]() {
	            id.fetch_add(1);
	
	            std::shared_ptr<Person> p1 = pool.get_object();
	            if (p1) {
	                p1->set_id(std::to_string(id)); 
	                p1->set_name(std::to_string(id));
	                LOG(INFO) << *p1;
	                LOG(INFO) << "thread_id:" << std::this_thread::get_id() 
	                << ",in_used:" << pool.in_used(); 
	                
	                std::this_thread::sleep_for(std::chrono::milliseconds(40));
	                pool.return_object(p1);
	            } else {
	                LOG(INFO) << "p1 is nullptr"; 
	            }
	        }));
	    }
	 
	    for (auto& th: threads) {
	        LOG(INFO) << "thread_id:" << std::this_thread::get_id();
	        th.join();
	    }
	
	    EXPECT_EQ(0, pool.in_used());
	}
	
	TEST(ObjectPoolTestSuite, object_pool_lockfree_test) {
	    ObjectPool<Person> pool;
	   
	    
	    size_t thread_size = 20; 
	    std::atomic<size_t> id(0); 
	    std::vector<std::thread> threads;
	    threads.reserve(thread_size);
	
	    for (size_t i = 0; i < thread_size; ++i) {
	        threads.push_back(std::thread([&]() {
	            id.fetch_add(1);
	
	            Person* p1 = pool.get_object_lockfree();
	            if (p1) {
	                p1->set_id(std::to_string(id)); 
	                p1->set_name(std::to_string(id));
	                LOG(INFO) << *p1;
	                LOG(INFO) << "thread_id:" << std::this_thread::get_id() 
	                << ",in_used:" << pool.in_used();
	                
	                std::this_thread::sleep_for(std::chrono::milliseconds(40));
	                pool.return_object_lockfree(p1);
	            } else {
	                LOG(INFO) << "p1 is nullptr" << std::endl; 
	            }
	        }));
	    }
	 
	    for (auto& th: threads) {
	        LOG(INFO) << "thread_id:" << std::this_thread::get_id();
	        th.join();
	    }
	
	    EXPECT_EQ(0, pool.in_used());
	}
	
	int main(int argc, char* argv[]) {
	    testing::InitGoogleTest(&argc, argv);
	    return RUN_ALL_TESTS();
	}

