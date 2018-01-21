#typeid and `is_base_of<T>`::value
##1 typeid
##1.1 示例
###1.1.1 eg1 
	#include <iostream>
	#include <string>
	#include <typeinfo>
	
	struct Person {
	    std::string name;
	    int age;
	};
	
	int main() {
	    Person someone = {"someone", 1};
	    std::cout << someone.name << ", " << someone.age << std::endl;
	    //jimmy:???
	    //why the result is:6Person ???
	    std::cout << typeid(someone).name() << std::endl;
	    return 0;
	}

##2 is_base_of<T>::value
##2.1 示例
###2.1.1 eg1
	
	#include <iostream>
	#include <type_traits>
	
	struct Person {
	    std::string name;
	    int age;
	};
	
	struct Student : public Person {
	    std::string grade;
	};
	
	int main() {
	    std::cout << std::boolalpha;
	    std::cout << std::is_base_of<int, int>::value << std::endl;
	    std::cout << std::is_base_of<Person, Student>::value << std::endl;
	    std::cout << std::is_base_of<Person, const Student>::value << std::endl;
	    std::cout << std::is_base_of<Student, Person>::value << std::endl;
	    
	    return 0;
	}  