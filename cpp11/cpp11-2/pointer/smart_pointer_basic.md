#智能指针

##0 背景
忘记释放内存或者多次重复释放内存都会导致严重错误,比如memory leak或者segmentation fault等。为了解决此问题，牛人们设计了智能指针.

其基本原理是把指针变量放在栈(而不是堆)上，这样当离开作用域(`unique_ptr`)或者引用数为0(`shared_ptr`)时，能够自动释放内存。解放程序员的大脑！

`auto_ptr`作为旧的智能指针已经被废弃，伙伴们，功能更加强大的`unique_ptr`和`shared_ptr`来了。

智能指针需要`#include <memory>`, 可以像普通指针那样使用`*`和`->`。

情非得已，尽可能得使用智能指针吧!

##1 定义/初始化/使用 智能指针

##1.1 定义/初始化
* 方法1: `std::shared_ptr<Person> p1(new Person("6103240001", "jimmy", 35));`
* 方法2: `auto p2 = std::make_shared<Person>("6103240002", "amao", 36);`

----
	#include <iostream>
	#include <memory>
	
	class Person {
	public:
	    Person(std::string id, std::string name, int age) : 
	        _id(id), _name(name), _age(age) {}
	
	    friend std::ostream& operator<<(std::ostream& out, const Person& p) {
	        out << p._id << "," << p._name << "," << p._age;
	        return out;
	    }
	private:
	    std::string _id;
	    std::string _name;
	    int _age;
	};
	
	int main() {
	    std::shared_ptr<Person> p1(new Person("610324001", "jimmy", 35));
	    std::cout << *p1 << std::endl;
	
	    auto p2 = std::make_shared<Person>("610324002", "amao", 36);
	    std::cout << *p2 << std::endl;
	}

##1.2 get()及用法

`get()`返回c类型的指针，用在需要c类型指针的地方。如：

	std::unique_ptr<char[]> buffer(new char[1024]);
	...
	int rc = ::write(fd, buffer.get(), len);

##1.3 reset()及用法
reset()能够将当前智能指针指向另一个new出来的对象地址。例如：`my_uni_ptr.reset(new int(4));`

##1.4 智能指针做函数返回值

`unique_ptr`和`shared_ptr`都可以直接从函数中作为返回值。

回想非智能指针时代，如果从函数中返回一个指针，则需要调用者考虑是否需要释放它。而有了智能指针，一切变得简单多了，just use it!

从函数中返回`unique_ptr`或者`shared_ptr`时，会自动调用std::move(),因为在定义`unique_ptr``shared_ptr`的头文件中，已经定义了右值拷贝构造函数。(其实也定义了`operator=(std::unique_ptr<T>&& rhs)`，我猜的:-))

	#include <unordered_map>

	//unordered_map的value部分是一个shared_ptr
	using StuffTable = std::unordered_map<std::string, std::shared_ptr<Person>>;

	//函数的返回值是个shared_ptr
	std::shared_ptr<Person> find_person_from_table(StuffTable table, std::string id) {
	    if (table.find(id) != table.end()) {
	        return table[id];
	    } else {
	        return nullptr;
	    }
	}
	
	int main() {
	    StuffTable table;
	
	    std::string p1_id = "610324001";
	    std::shared_ptr<Person> p1(new Person(p1_id, "jimmy", 35));
	    table[p1_id] =  p1;
	
	    std::string p2_id = "610324002";
	    auto p2 = std::make_shared<Person>(p2_id, "amao", 36);
	    table[p2_id] = p2;
	
	    std::string to_find_id = "610324002";
	    auto found_p = find_person_from_table(table, to_find_id);
	    if (found_p) {
	        std::cout << *found_p << std::endl;
	    } else {
	        std::cout << "not found" << std::endl;
	    }
	}

##1.5 智能指针赋给另一个智能指针

`shared_ptr`可以直接用等号`=`赋给另一个`shared_ptr`,但`unique_ptr`禁止这么做，可以借助`std::move()`来完成。为什么呢？因为`unique_ptr`同一个时刻只支持一个`unique_ptr`指向这个对象地址。std::move()只是把其变为&&右值引用，然后交个template <class T> std::unique<T>& operator=(std::unique<T>&& other)来完成，其会清除掉orig的。

###1.5.1 把`shared_ptr`指向另一个`shared_ptr`

	std::string p1_id = "610324001";
    std::shared_ptr<Person> p1(new Person(p1_id, "jimmy", 35));
    auto p2 = p1;
    std::cout << *p2 << std::endl;
	

###1.5.2 把`unique_ptr`指向另一个`unique_ptr`
**Note!!!:**必须借助std::move(),因为同一时刻，只能一个`unique_ptr`指向这块内存地址。
		
	std::string p1_id = "610324001";
    std::unique_ptr<Person> p1(new Person(p1_id, "jimmy", 35));
    auto p2 = std::move(p1);  //std::move
    std::cout << *p2 << std::endl;

##2 注意

###2.1 `unique_ptr`没有`make_unique`
cpp11有`make_shared`但却没有`make_unique`,是不是很不公平？据说cpp14才有了。不过，如果实在想用，也没有关系。只要下来代码即可：

	template<typename T, typename... Args>
	std::unique_ptr<T> make_unique(Args&&... args) {
	    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

例子：
	
	class Person {
	public:
	    Person(std::string name, int age) : _name(name), _age(age) {}
	    std::string _name;
	    int _age;
	};

	template<typename T, typename... Args>
	std::unique_ptr<T> make_unique(Args&&... args) {
	    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

	int main() {
	    std::unique_ptr<std::string> u_ptr = make_unique<std::string>("cao");
	    std::cout << *u_ptr << std::endl;
	
	    std::unique_ptr<Person> upp = make_unique<Person>("jimmy", 32);
	    std::cout << upp->_name << "," << upp->_age << std::endl;
	}

###2.2 区分`unique_ptr`和`unique_lock`
名字里都有unique，但意义大不同。你注意到了吗？

##3 直升机：现实中的例子

###3.1 eg1
	std::unique_ptr<int> u_ptr(new int(1));
    if (u_ptr) {
        std::cout << "not nullptr" << std::endl;
    }
    //here, we test * to a unique_ptr
    std::cout << *u_ptr << std::endl;
    std::cout << *u_ptr.get() << std::endl;

    std::unique_ptr<int> u_ptr2;
    if (!u_ptr2) {
        std::cout << "nullptr" << std::endl;
    }

    //u_ptr2 = u_ptr; //error, = is deleted
    //std::unique_ptr<int> u_ptr3(u_ptr); //error, deleted
    
    //the u_ptr is cleared not by std::move()
	//but by 'template <class T> std::unique<T>& operator=(std::unique<T>&& other)'
    u_ptr2 = std::move(u_ptr);
    if (u_ptr2 && !u_ptr) {
        std::cout << "after move, u_ptr2 is non-nullptr, while u_ptr is nullptr now" << std::endl;
    }

    std::unique_ptr<int> u_ptr4(std::move(u_ptr2));
    if (u_ptr4 && !u_ptr2) {
        std::cout << "after move, u_ptr4 is non-nullptr, while u_ptr2 is nullptr now" << std::endl;
    }
    //currently, only u_ptr4  pointer to the new int(1)
    std::cout << "value:" << *u_ptr4.get() << std::endl;
    //std::cout << "value:" << *u_ptr2.get() << std::endl; //error, will seg fault, because the memory is freed 

##3.2 eg2
	
	void test1() {
	    std::unique_ptr<int> u_ptr(new int(3));
	    std::cout << *u_ptr << std::endl; 
	    std::cout << *u_ptr.get() << std::endl;
	    std::cout << *(int*)u_ptr.get() << std::endl;
	
	    u_ptr.reset(new int(4));
	    std::cout << * static_cast<int*> (u_ptr.get()) << std::endl;
	}

	struct Person {
	    Person(std::string n, int a) : name(n), age(a) {}
	    std::string name;
	    int age;
	    virtual void print() {
	        std::cout << name << " " << age << std::endl;
	    }
	};
	
	struct Student : public Person {
	    Student(std::string n, int a, int g) : Person(n, a), grade(g) {} 
	    int grade;
	    virtual void print() {
	        std::cout << name << " " << age << " " << grade << std::endl;
	    }
	};

	void test2() {
	    std::vector<std::unique_ptr<Person>*> p_vec;
	
	    std::unique_ptr<Person> p1(new Person("cao", 34));
	    p_vec.push_back(&p1);
	
	    std::unique_ptr<Person> p2(new Person("jimmy", 33));
	    p_vec.push_back(&p2);
	
	    for (const auto& p : p_vec) {
	        std::cout << (*p)->name << ":" << (*p)->age << std::endl;
	    }
	}
	
	void test3() {
	    std::vector<std::unique_ptr<Person>> p_vec;
		//std::move for std::unique_ptr
		//Notice:
		//std::unique_ptr is uncopyable(can not =), while vector needs it, 
		//so just use std::move()!!!!
	    std::unique_ptr<Person> p1(new Person("cao", 34));
	    p_vec.push_back(std::move(p1));
	
	    std::unique_ptr<Person> p2(new Person("jimmy", 33));
	    p_vec.push_back(std::move(p2));
	
	    for (const auto& p : p_vec) {
	        std::cout << p->name << ":" << p->age << std::endl;
	    }
	}
	
	void test4() {
	    std::unique_ptr<Person> p_ptr(new Person("lin", 31));
	    std::cout << p_ptr->name << ":" << p_ptr->age << std::endl;
	    
	    p_ptr.reset(new Student("mumu", 2, 1));
	    //p_ptr.get will get the real address
	    std::cout << ((Student*)p_ptr.get())->grade << std::endl;
	}
	
	void test5() {
	    std::unique_ptr<Student> s_ptr(new Student("mumu", 2, 1)); 
	
	    std::unique_ptr<Person> p_ptr(std::move(s_ptr));
	    std::cout << p_ptr->name << ":" << p_ptr->age << std::endl;
	    //std::cout << p_ptr->grade << std::endl; // error, since person have no 'grade' member
	    //when use dynamic_cast, base must have virtual functions
	    std::cout << dynamic_cast<Student*>(p_ptr.get())->grade << std::endl;
	}

##3.3 eg3
	template<class AGG>
	//typename表明Result_type是AGG的一个类型成员，而非static变量
	void Accumulator::read(typename AGG::Result_type& ret) {
		AccumulatorReader::singleton().read<AGG>(_id, ret); //singleton设计模式
	}

	template<class AGG>
	std::unique_ptr<Accumulator<AGG>> create_accumulator(const std::string& name, size_t max_cached_count = 10) {
		return std::unique_ptr<Accumulator<AGG>>(new Accumulator<AGG>(name, max_cached_count));
	}

	template<class AGG>
	std::unique_ptr<typename AGG::Result_type> get_accumulator_result(const std::string& name) {
		auto acc = create_accumulator<AGG>(name);
		auto ret = std::unique_ptr<typename AGG::Result_type>(new typename AGG::Result_type());
		read(*ret.get()); //get()返回的是一个c类型的指针
		return ret;
	}


###3.4 eg4 `shared_ptr dynamic_cast`

	#include <iostream>
	#include <memory>
	#include <string>
	
	struct Person { 
	    Person(std::string n, int a) : name(std::move(n)), age(a) {}
	    std::string name;
	    int age;
	    virtual void print()  {
	        std::cout << name << "," << age << std::endl;
	    }
	};
	
	class Student : public Person {
	public:
	    Student(std::string n, int a, int g) : Person(n, a), grade(g) {}
	    int grade;
	    virtual void print() {
	        std::cout << name << "," << age << "," << grade << std::endl;
	    }
	};
	
	std::shared_ptr<Person> get_person1() {
	    std::shared_ptr<Person> p_person(new Person{"jimmy", 35});
	    return p_person;
	}
	
	std::shared_ptr<Person> get_person2() {
	    std::shared_ptr<Person> p_person = std::make_shared<Person>("cao", 36);
	    return p_person;
	}
	
	int main() {
	    std::shared_ptr<Person> sp_p1 = get_person1();
	    std::cout << sp_p1->name << "," << sp_p1->age << std::endl;
	
	    std::shared_ptr<Person> sp_p2 = get_person2();
	    std::cout << sp_p2->name << "," << sp_p2->age << std::endl;
	
	
	    std::shared_ptr<Person> sp_p3 = std::make_shared<Student>("mumu", 4, 1);
	    std::cout << sp_p3->name << "," << sp_p3->age << std::endl;
	    //std::cout << pp3->grade << std::endl; //error
	
	    Student* ps4 = dynamic_cast<Student*> (sp_p3.get());
	    std::cout << ps4->name << "," << ps4->age << "," << ps4->grade << std::endl;
	    
	    return 0;
	}


###4.6 `unique_ptr, dynamic_cast`

	#include <iostream>
	#include <vector>
	#include <memory>
	void test1() {
	    std::unique_ptr<int> u_ptr(new int(3));
	    std::cout << *u_ptr << std::endl; 
	    std::cout << *u_ptr.get() << std::endl;
	    std::cout << *(int*)u_ptr.get() << std::endl;
	
	    u_ptr.reset(new int(4));
	    std::cout << * static_cast<int*> (u_ptr.get()) << std::endl;
	}
	
	
	
	struct Person {
	    Person(std::string n, int a) : name(n), age(a) {}
	    std::string name;
	    int age;
	    virtual void print() {
	        std::cout << name << " " << age << std::endl;
	    }
	};
	
	struct Student : public Person {
	    Student(std::string n, int a, int g) : Person(n, a), grade(g) {} 
	    int grade;
	    virtual void print() {
	        std::cout << name << " " << age << " " << grade << std::endl;
	    }
	};
	
	
	void test2() {
	    std::vector<std::unique_ptr<Person>*> p_vec;
	
	    std::unique_ptr<Person> p1(new Person("cao", 34));
	    p_vec.push_back(&p1);
	
	    std::unique_ptr<Person> p2(new Person("jimmy", 33));
	    p_vec.push_back(&p2);
	
	    for (const auto& p : p_vec) {
	        std::cout << (*p)->name << ":" << (*p)->age << std::endl;
	    }
	}
	
	void test3() {
	    std::vector<std::unique_ptr<Person>> p_vec;
	//std::move for std::unique_ptr
	//Notice:
	//std::unique_ptr is uncopyable(can not =), while vector needs it
	//so just use std::move()!!!!
	    std::unique_ptr<Person> p1(new Person("cao", 34));
	    p_vec.push_back(std::move(p1));
	
	    std::unique_ptr<Person> p2(new Person("jimmy", 33));
	    p_vec.push_back(std::move(p2));
	
	    for (const auto& p : p_vec) {
	        std::cout << p->name << ":" << p->age << std::endl;
	    }
	}
	
	void test4() {
	    std::unique_ptr<Person> p_ptr(new Person("lin", 31));
	    std::cout << p_ptr->name << ":" << p_ptr->age << std::endl;
	    
	    p_ptr.reset(new Student("mumu", 2, 1));
	    //p_ptr.get will get the real address
	    std::cout << ((Student*)p_ptr.get())->grade << std::endl;
	}
	
	void test5() {
	    std::unique_ptr<Student> s_ptr(new Student("mumu", 2, 1)); 
	
	    std::unique_ptr<Person> p_ptr(std::move(s_ptr));
	    std::cout << p_ptr->name << ":" << p_ptr->age << std::endl;
	    //std::cout << p_ptr->grade << std::endl; // error, since person have no 'grade' member
	    //when use dynamic_cast, base must have virtual functions
	    std::cout << dynamic_cast<Student*>(p_ptr.get())->grade << std::endl;
	}
	
	
	int main() {
	    std::cout << "-----1-------------------" << std::endl;
	    test1();
	    std::cout << "-----2-------------------" << std::endl;
	    test2();
	    std::cout << "-----3-------------------" << std::endl;
	    test3();
	    std::cout << "------4------------------" << std::endl;
	    test4();
	    std::cout << "------5------------------" << std::endl;
	    test5();
	    return 0;
	}

###4.6

	#include <iostream>
	#include <memory>
	int main() {
	    std::unique_ptr<int> u_ptr(new int(1));
	    if (u_ptr) {
	        std::cout << "not nullptr" << std::endl;
	    }
	    //here, we test * to a unique_ptr
	    std::cout << *u_ptr << std::endl;
	    std::cout << *u_ptr.get() << std::endl;
	
	    std::unique_ptr<int> u_ptr2;
	    if (u_ptr2 == nullptr) {
	        std::cout << "nullptr" << std::endl;
	    }
	
	    if (!u_ptr2) {
	        std::cout << "nullptr" << std::endl;
	    }
	
	    //u_ptr2 = u_ptr; //error, = is delted
	    //std::unique_ptr<int> u_ptr3(u_ptr); //error, deleted
	    
	
	    //jimmy:!!!!!
	    //the u_ptr is cleared not by std::move(), but by 'template <class T> std::unique<T>& operator=(std::unique<T>&& other)'
	    u_ptr2 = std::move(u_ptr);
	    if (u_ptr2 && !u_ptr) {
	        std::cout << "after move, u_ptr2 is non-nullptr, while u_ptr is nullptr now" << std::endl;
	    }
	
	    std::unique_ptr<int> u_ptr4(std::move(u_ptr2));
	    if (u_ptr4 && !u_ptr2) {
	        std::cout << "after move, u_ptr4 is non-nullptr, while u_ptr2 is nullptr now" << std::endl;
	    }
	    //currently, only u_ptr4  pointer to the new int(1)
	    std::cout << "value:" << *u_ptr4.get() << std::endl;
	    //std::cout << "value:" << *u_ptr2.get() << std::endl; //error, will seg fault, because the memory is freed 
	
	    return 0;
	}