#mutable

##mutable lambda
	#include <iostream>
	#include <functional>
	
	int main() {
	    int x = 0;
	    auto f1 = [=]() mutable {x = 42; std::cout << x << std::endl;};
	    //auto f2 = [=]()  {x = 42;}; //error, x is captured by value'=', can not changed
	    f1();
	    //x is still 0, but in lamda, it is changed value
	    std::cout << x << std::endl;
	}

##mutable member
	
	#include <iostream>
	#include <memory>
	
	
	class Person {
	public:
	    Person(std::string name, int age, bool married, int married_check_num=0) 
	        : _name(std::move(name)), _age(age), _married(married), _married_query_num(married_check_num) { 
	    }
	
	    //!!Notice:
	    // even the function is const, 
	    // however, _married_query_num is declared as 'mutable'
	    bool married() const {
	        ++_married_query_num;
	        return _married;
	    }
	
	    friend std::ostream& operator<<(std::ostream& out, const Person& p) {
	        out << p._name << "," 
	            << p._age << "," 
	            << p._married 
	            << ", married_check_num:" 
	            << p._married_query_num
	            << std::endl;         
	        return out;
	    }
	    
	private:
	    std::string _name="";
	    int _age = 0;
	    bool _married = false;
	    mutable int _married_query_num;
	};
	
	int main() {
	    Person me("cao", 35, true);
	    std::cout << "married:" << me.married() << std::endl;
	    std::cout << me << std::endl;
	    return 0;
	}