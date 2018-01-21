#lambda表达式#

##0 简介##
* lambda表达式是一种无名函数
* 在该无名函数中可以capture一些外面的变量
* 具有局部生命周期
* lambda表达式原理上相似与函数指针和函数对象

##1 简单示例 ##
	
	std::vector<int> numbers = {1, 2, 3, 4}; 
    std::for_each(numbers.begin(), numbers.end(), 
				[](int i){ std::cout << i << std::endl; } );
	
	//每个iterator的值将作为lambda函数的参数i传入

	[](int i) { std::cout << i << std::endl;} (999);
	//在末尾加入(999)来传入值，并直接调用

	auto func1 = [](int i) { std::cout << i << std::endl; };
    func1(888);

实质上，lambda表达式通常用在某些地方(in place)而无需函数声明。如果逻辑足够复杂，还是定义一个有名函数或者函数对象为妙 :）。

##2 从lambda表达式return##
	
	if ([](int a, int b) { return 2*a == b;} (12, 24)) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }

	std::cout << "the return is :" << 
		[](double a, double b) -> int { return a+b;} (3.3, 4.4) 
		<< std::endl;

##3 capture上下文，巨牛X的特性 ##

###3.1 传引用和传值 ###
	
**如果是传值，[ ]会captrue并store住lambda表达式声明时刻上下文中的变量。例如：**

	int a = 1;
    auto func1 = [a] {std::cout << a ;};

    for (int i = 0; i < 3; i++) {
        func1();
        ++a;
    }
	//Note： output为：1 1 1，并没有随着++a而改变
**如果是传引用，则lambda中修改的值会改变外部变量的值**

	int a = 1;
    double b = 3.14;

    [&a, b]() mutable {  
        std::cout << "a:" << a << ", b:" << b << std::endl;
        a = 2;
		b = 3.1415; //mutable is a must, o/w b cannot be changed
    } ();

    std::cout << "a:" << a << ", b:" << b << std::endl;  //a:2, b:3.14

[&a, b]使用了capture特性，&a表明以引用方式capture， 故a = 2会修改其值；而b是以值方式capture，虽然通过mutable可以修改之，但因为是值传递，并不影响外面b的值。 这和对一个函数对象通过传参数方式初始化类同，如下：

	class FuncObject {
    public:
        FuncObject(int& a, int b) : _a(a), _b(b) {}

        void operator()() {
            _a = 3; 
        }
    private:
        int& _a;
        double _b;
    };

    FuncObject fo(a, b);
    fo();
    std::cout << "a:" << a << ", b:" << b << std::endl;



###3.2 [=][&]###
[=]capture传值

[&]capture引用

**试想，如果有很多外部变量要capture，如果一个个列出来累死人啊，故[=][&]多方便！:-)**

##4 lamdba和algo的结合##

###4.1 原始例子 ###

	#include <iostream>
	#include <list>
	#include <fstream>
	
	class Person {
	public:
	    Person(std::string id="", std::string name="", int age=0) : 
	        _id(id), _name(name), _age(age){}
	
		//设计理念：对一个对象而言，可能有主动行为，如sing(), run(); 
		//也可能有被动行为,如save()，kill(), 通过抽象，都可以作为成员函数
		//Note!!!: 这里ostream做参数，即把自己save到ostream中
	    void save(std::ostream& os) {
	        os << "id:" << _id << ",name:" << _name 
	            << ",age:" << _age << std::endl;
	    }
	
	    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
	        os << "id:" << p._id << ",name:" << p._name 
	            << ",age:" << p._age;
	        return os; 
	    }
	
	private:
	    std::string _id;
	    std::string _name;
	    int _age;
	};

	int main() {
	    std::ofstream out_file("person.txt");
	    std::list<Person*> plist;
	    for (int i = 0; i < 10; ++i) {
	        Person* p = new Person("10000"+std::to_string(i), 
	                "jimmy"+std::to_string(i),
	                30+i);
	        plist.push_back(p);
	    }
	
	    for (auto iter = plist.begin(); iter != plist.end(); ++iter) {
	        (*iter)->save(out_file);
	        std::cout << **iter << std::endl; //operator<<接收person&做参数
	        delete(*iter); //释放内存
	    }
	
	    std::cout << plist.size() << std::endl;
	}

###4.2 function object + algo ###

为了突出，只列出核心代码。

	#include <algorithm>
	class MemSavor {
	public:
	    MemSavor(std::ostream& os) : _os(os) {}
	    void operator()(Person* p) {
	        p->save(_os);
	    }
	private:
	    std::ostream& _os;
	};	
	
	//in main
	for_each(plist.begin(), plist.end(), MemSavor(out_file));

###4.3 lamda + algo 	

	for_each(plist.begin(), plist.end(), 
		[&out_file](Person* p){p->save(out_file);} );

super cool, right?

##5 [this]让lamdba能够capture类成员变量

Note:!!!类成员变量不是局部变量，故通过[&][=]是不能capture的，别急，[this]来救驾了！

###5.1 原始例子
	
	#include <iostream>
	#include <list>

	class Accumulator{
	public:
	    Accumulator(std::list<int>& numbers, int criterion) :
	        _numbers(numbers), _criterion(criterion), _count(0) {}
	
	    int get_over_criterion() {
	        for (auto i : _numbers) {
	            if (i > _criterion) {
	                ++_count;
	            }
	        }
	        return _count;
	    }
	
	private:
	    std::list<int> _numbers;
	    int _criterion;
	    int _count;
	};
	
	int main() {
	    std::list<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	    Accumulator acc(numbers, 5);
	    std::cout << acc.get_over_criterion() << std::endl;
	}

###5.2 [this]

	int get_over_criterion() {
        for_each(_numbers.begin(), _numbers.end(), 
                [this](int i){
                    if (i > _criterion) {
                        ++_count;
                    }
                });
        return _count;
    }

##6 示例
###6.1 eg1

	#include <iostream>
	#include <algorithm>
	
	class MyClass {
	public:
	    MyClass(int min = 0, int max = 999) : _min(min), _max(max) {
	        for (int i = 0; i < 10; ++i) {
	            _vec.push_back(i);
	        }
	    }
	
	    void test_by_this() {
	        auto it = std::find_if(_vec.begin(), _vec.end(), [this](int i){return i > _min && i < _max;});
	        std::cout << *it << std::endl;
	    }
	
	    void test_by_value() {
	        auto it = std::find_if(_vec.begin(), _vec.end(), [=](int i){return i > _min && i < _max;});
	        std::cout << *it << std::endl;
	    }
	
	    void test_by_ref() {
	        auto it = std::find_if(_vec.begin(), _vec.end(), [&](int i){return i > _min && i < _max;});
	        std::cout << *it << std::endl;
	    }
	    
	private:
	    int _min;
	    int _max;
	    std::vector<int> _vec;
	};
	
	
	int main() {
	    MyClass my(4, 6);
	    my.test_by_this();
	    my.test_by_value();
	    my.test_by_ref();
	    return 0;
	}

###6.2 eg2 `lamda_func`

	#include <iostream>
	#include <string>
	#include <vector>
	#include <algorithm>
	
	class Functor {
	public:
	    bool operator()(int i) {
	        return i > 4;
	    }
	
	};
	
	int main() {
	    std::vector<int> vec;
	    for (int i = 0; i < 10; ++i) {
	        vec.push_back(i);
	    }
	
	    //functor
	    auto it1 = std::find_if(vec.begin(), vec.end(), Functor());
	    std::cout << *it1 << std::endl;
	
	    //lamda
	    auto it2 = std::find_if(vec.begin(), vec.end(), [](int i){ return i > 4;});
	    std::cout << *it2 << std::endl;
	
	    //function and lamda
	    std::function<bool(int)> my_func = [](int i) { return i > 4; };
	    auto it3 = std::find_if(vec.begin(), vec.end(), my_func);
	    std::cout << *it3 << std::endl;
	
	    //lamda return
	    std::function<int(int)> square = [](int i) -> int { return i * i; };
	    std::cout << "4 * 4 =" << square(4) << std::endl;
	
	    //--------------------------------------------
	    int min = 4, max = 6;
	
	    auto it4 = std::find_if(vec.begin(), vec.end(), [=](int i){return i > min && i < max;});
	    std::cout << *it4 << std::endl;
	
	    auto it5 = std::find_if(vec.begin(), vec.end(), [&](int i){return i > min && i < max;});
	    std::cout << *it5 << std::endl;
	   
	    
	    auto it6 = std::find_if(vec.begin(), vec.end(), [=, &max](int i){return i > min && i < max;});
	    std::cout << *it6 << std::endl;
	    
	    //--------------------------------------------
	    size_t sum_larger_4 = std::count_if(vec.begin(), vec.end(), [=](int i) {return i > 4;});
	    std::cout << "sum_large_4:" << sum_larger_4 << std::endl;
	    return 0;
	}


###6.3 eg3

	#include <iostream>
	#include <functional>
	
	int get_num1() {
	    int num = 1;
	    //jimmy: 
	    //& is give the reference of num to lamda function
	    // void<void> is a mnust
	    std::function<void(void)> func = [&](){
	            std::cout << "in lamda:" << num << std::endl;
	            num++;
	        };
	
	    func();
	    return num;
	}
	
	int get_num2() {
	    int num = 2;
	    //jimmy:
	    //= will transfer by value, num will keep remained value
	    //->int indicates the return value of this lamda function
	    std::function<int(void)> func = [=]()->int {
	       int tmp = num;
	       tmp++;
	       return tmp;
	    };
	
	    return func();
	}
	
	int get_num3() {
	    int num = 3;
	    std::function<void(void)> func = [&]() {
	        ++num;
	    }; 
	    
	    return (func(), num);
	 }
	
	int main() {
	    std::cout << "returned form get_num1:" << get_num1() << std::endl;
	    std::cout << "returned form get_num2:" << get_num2() << std::endl;
	    std::cout << "returned form get_num3:" << get_num3() << std::endl;
	    
	    return 0;
	}

###6.4 address_lamda
	
	#include <iostream>
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
	
	typedef std::function<bool(std::string&)> Func;
	
	class Address {
	    public:
	        Address(std::vector<std::string>& addr_book) : _addr_book(addr_book) {}
	
	        std::vector<std::string> filter(Func func) {
	            std::vector<std::string> results;
	            for (auto& item : _addr_book) {
	                if(func(item)) {
	                    results.push_back(item);
	                }
	            }
	            return std::move(results);
	        }
	
	    private:
	        std::vector<std::string> _addr_book;
	};
	
	class FilterClass {
	public:
	    FilterClass(std::string& to_filter_str) : _to_filter_str(std::move(to_filter_str)) {}
	
	    bool operator()(std::string& item)  {
	        if (item.find(_to_filter_str) != std::string::npos) {
	            return true;
	        } else {
	            return false;
	        }
	    }
	    private:
	        std::string _to_filter_str;
	};
	
	int main() {
	    std::vector<std::string> firms = {"www.sina.com", "www.qq.com", "www.hust.edu.cn", "www.xjtu.edu.cn"};
	    
	    std::string to_filter_str = "com";
	    Func func = [&](std::string& item) {
	        if (item.find(to_filter_str) != std::string::npos) {
	            return true;
	        }
	        return false;
	    };
	
	    Address addr(firms);
	
	    std::vector<std::string> results = addr.filter(func);
	    std::copy(results.begin(), results.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	   
	    std::string to_filter_str2 = "cn";
	    std::vector<std::string> results2 = addr.filter(FilterClass(to_filter_str2));
	    std::copy(results2.begin(), results2.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	    return 0;
	}
