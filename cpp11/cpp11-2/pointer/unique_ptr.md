	
	#include <iostream>
	#include <memory>
	
	template<class T, class... ARGS>
	std::unique_ptr<T> make_unique(ARGS && ... args) {
	    return std::unique_ptr<T>(new T(std::forward<ARGS>(args)...));
	}
	
	class Person {
	public:
	    Person(int age, std::string& name) : _age(age), _name(name) {
	    }
	
	    ~Person() = default;
	    
	    friend std::ostream& operator<< (std::ostream& out, const Person& p) {
	        out << "name:" << p._name << ", age:" << p._age;
	    }
	private:
	    int _age;
	    std::string _name;
	};
	
	std::unique_ptr<Person> get_person(int age, std::string& name) {
	    std::unique_ptr<Person> person_ptr = make_unique<Person>(age, name);
	    return person_ptr; 
	}
	
	int main() {
	    int age = 10;
	    std::string name = "jimmy";
	    std::unique_ptr<Person> pp = get_person(age, name);
	    std::cout << *pp << std::endl;
	}
