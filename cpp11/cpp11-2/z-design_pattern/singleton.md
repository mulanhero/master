#Singleton

##0 背景

##1. 


###1.2 实现方法
在public中实现，例如(为了只提供singleton接口，一般把构造函数隐藏在private中)：

	static ClassName& singleton() {
		static ClassName c;
		return c;
	}

##2 示例
###2.1 eg1
	
	#include <iostream>
	#include <queue>
	
	class Single {
	public:
	    static Single& singleton() {
	        static Single s;
	        return s;
	    }
	
	    void write(int e) {
	        q.push(e);
	    }
	
	    int read() {
	        int e = q.front();
	        q.pop();
	        return e;
	    }
	
	    size_t size() {
	        return q.size();
	    }
	
	private:
		Single() = default;
	    std::queue<int> q;
	};
	
	
	int main() {
	    Single s = Single::singleton();
	    s.write(1);
	    s.write(2);
	    std::cout << "size:" << s.size() << std::endl; 
	    std::cout << "read:" <<  s.read() << std::endl;
	    std::cout << "size:" << s.size() << std::endl; 
	    std::cout << "read:" <<  s.read() << std::endl;

		Single::singleton().write(3);
    	std::cout << Single::singleton().size() << std::endl;
    	Single::singleton().read();
	
	    return 0;
	}