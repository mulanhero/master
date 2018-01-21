#用gdb调试core#

##0 简介##
如果指针使用不当，最常见出现segmentation fault错误。我们可以根据core文件来调试。

##1 code ##
以下面的一段code为例

	#include <iostream>
	template <class KEY, class VALUE>
	struct node_t {
    	KEY key;
    	VALUE value;
    	node_t* prev;
    	node_t* next;

	    node_t(): key(KEY()), value(VALUE()), prev(nullptr), next(nullptr) {
	    }

	    friend bool operator<(const node_t& n1, const node_t& n2) {
	        return n1.key < n2.key ? true : false;
	    }

	    friend bool operator==(const node_t& n1, const node_t& n2) {
	        if (&n1 == &n2 || n1.key == n2.key) {
	            return true;
	        } else {
	            return false;
	        }
	    }
	};

	template <class KEY, class VALUE>
	class ordered_list {
	public:
	    ordered_list() : _head(nullptr), _size(0){
	        _head = new node_t<KEY,VALUE>();
	    }

	    virtual ~ordered_list() {
	        node_t<KEY,VALUE>* tmp = _head->next;
	        while (tmp) {
	            node_t<KEY,VALUE>* next = tmp->next;
	            delete tmp;
	            tmp = next;
	        }
	
	        delete _head;
	    } 

	    void print() {
	        std::cout << "size :" << _size << std::endl;    
	        node_t<KEY, VALUE>* tmp = _head->next;
	        while (tmp) {
	            std::cout << "[" << tmp->key << "," << tmp->value << "] ";
	            tmp = tmp->next;
	        }
	        std::cout << std::endl;
	    }
    
	    void insert(KEY key, VALUE value) {
	       node_t<KEY, VALUE>* node = new node_t<KEY,VALUE>(); 
	       node->key = key;
	       node->value = value;
	       node->prev = node->next = nullptr;
	       ++_size;
	
	       if (!_head->next) {
	            _head->next = node;
	            node->prev = _head;
	            return;
	       }
	
	       node_t<KEY,VALUE>* tmp = _head->next;
	       node_t<KEY,VALUE>* last = _head; 
	       while (tmp) {
	            if (key > tmp->key) {
	               last = tmp;
	               tmp = tmp->next;
	               continue;
	            } else {
	                break;
	            }
	       }
	       
	        node->next = tmp;
	        node->prev = last;
	        last->next = node;
	       // if (tmp) {
	            tmp->prev = node;
	        //} 
	    }

	    size_t size() {
	        return _size;
	    }
    
		private:
		    node_t<KEY, VALUE>* _head;
		    size_t _size;
		};

	int main() {
	    ordered_list<std::string, int> mylist;
	    mylist.insert("610324", 34);
	    mylist.insert("610325", 32);
	
	    
	    std::cout << mylist.size() << std::endl;
	    mylist.print();
	    return 0;
	}
##2 用ulimit让程序调试时出core###
	
	ulimit -a  //check the config of ulimit 
	ulimit -c unlimit //make the core file unlimited

##3 编译、调试 ##
	
	[jimmy@centos7 algo]$ g++ -g list.cpp 
	[jimmy@centos7 algo]$ ./a.out 
	Segmentation fault (core dumped)
	[jimmy@centos7 algo]$ gdb a.out core.15594 
	Program terminated with signal 11, Segmentation fault.
	#0  0x0000000000401352 in ordered_list<std::string, int>::insert (this=0x7fff9265d370, key=..., value=32) at list.cpp:83
	83                  tmp->prev = node;
	
接下来，我们去检查第83行，发现tmp如果为nullptr，则不可能有prev指针，所以，我们把
	
	// if (tmp) {
		tmp->prev = node;
	//} 
改写成为

	if (tmp) {
		tmp->prev = node;
	}
重新执行，成功！
	
	