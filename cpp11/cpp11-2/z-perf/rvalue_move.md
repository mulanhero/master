#0 lvalue and rvalue
	lvalue should had been named something like "variable"   
	rvalue should had been named something like "temp"  
	Anything not having name is rvalue otherwise it's lvalue 
#1 eg	
	#include <iostream>
	#include <vector>
	
	struct City {
	    std::string _name;
	    int _postcode;
	};
	
	class CityBook {
	public:
	    CityBook(std::vector<City>& city_vec) : _size(city_vec.size()) {
	        if (_size > 0) {
	            _cities = new City[_size];
	            for (int i = 0; i < _size; ++i) {
	                _cities[i]._name = city_vec[i]._name;
	                _cities[i]._postcode = city_vec[i]._postcode;
	            }
	        }
	    }
	
	    ~CityBook() {
	        delete [] _cities;
	    }
	
	
	    CityBook(CityBook& other) {
	        _size = other.size();
	        if (_size > 0) {
	            _cities = new City[_size];
	            for (int i = 0; i < _size; ++i) {
	                _cities[i]._name = other.cities()[i]._name;            
	                _cities[i]._postcode = other.cities()[i]._postcode;            
	            }
	        }
	    }
	
	    CityBook& operator=(CityBook& other) {
	        _size = other.size();
	        if (_size > 0) {
	            _cities = new City[_size];
	            for (int i = 0; i < _size; ++i) {
	                _cities[i]._name = other.cities()[i]._name;            
	                _cities[i]._postcode = other.cities()[i]._postcode;            
	            }
	        }
	        return *this;
	    }
	
	    CityBook(CityBook&& other) {
	        _size = other.size();
	        _cities = other._cities;
	        other._cities = nullptr;
	        other._size = 0;
	    }
	
	    CityBook& operator=(CityBook&& other) {
	        _size = other.size();
	        _cities = other._cities;
	        other._cities = nullptr;
	        other._size = 0;
	        return *this;
	    }
	
	    void print() {
	        std::cout << "_size:" << _size << std::endl;
	        if (!_cities) {
	            std::cout << "nullptr" << std::endl;
	            return;
	        }
	        for (int i = 0; i < _size; ++i) {
	            std::cout << i << ",name:" << _cities[i]._name << ", postcode:" << _cities[i]._postcode << std::endl;
	        }
	    }
	
	    int size() {
	        return _size;
	    }
	
	    City* cities() {
	        return _cities;
	    }
	
	private:
	    int _size;
	    City* _cities;
	};
	
	int main() {
	    City c1 = {"beijing", 10};
	    City c2 = {"shanghai", 20};
	    std::vector<City> city_vec(2);
	    city_vec[0] = c1;
	    city_vec[1] = c2;
	
	    CityBook city_book1(city_vec); 
	    city_book1.print();
	
	    std::cout << "---normal constructor and operator= with deeply_copy-------" << std::endl;
	    CityBook city_book2(city_book1);
	    city_book2.print();
	
	    CityBook city_book3(city_book1);
	    city_book3.print();
	
	    city_book1.print();
	
	    std::cout << "---rvalue constructor and operator= with std::move()-------" << std::endl;
	    CityBook city_book_rvalue1(std::move(city_book1)); //CityBook has the && constructor, so std::move() is to change lvalue to rvalue
	    city_book_rvalue1.print();
	    city_book1.print();
	
	    CityBook city_book_rvalue2 = std::move(city_book_rvalue1); //same as the above, std::move is to change lvalue to rvalue
	    city_book_rvalue2.print();
	    city_book_rvalue1.print();
	
	    std::cout << "------push rvalue with std::move() to vector--------" << std::endl;
	    std::vector<CityBook> city_books;
	    city_books.push_back(std::move(city_book2));   //city_books has the && constructor, so std::move is to change lvalue to rvalue
	    city_books.push_back(std::move(city_book3));
	    for (auto& it : city_books) {
	        it.print();
	    }
	    city_book2.print();
	    city_book3.print();
	   
	    return 0;
	}
#2 eg		
	#include <iostream>
	#include <vector>
	#include <iterator>
	#include <ostream>
	
	class Person {
	public:
	    Person(int age, std::string& name) : _age(age), _name(name) {}
	
	    Person(Person& p) {
	        _age = p._age;
	        _name = p._name;
	    }
	
	    Person& operator=(Person& p) {
	        _age = p._age;
	        _name = p._name;
	        return *this;
	    }
	
	    Person(Person&& p) {
	        cons_rvalue(std::move(p));
	    }
	
	    Person& operator=(Person&& p) {
	        cons_rvalue(std::move(p));
	        return *this;
	    }
	
	    friend std::ostream& operator<<(std::ostream& out, Person& p) {
	        out << "name:" << p._name << ", age:" << p._age;
	        return out;
	    }
	private:
	    void cons_rvalue(Person&& p) {
	        _age = p._age;
	        _name = std::move(p._name);
	        p._age = 0;
	    }
	
	    int _age;
	    std::string _name;
	};
	
	int main() {
	    std::vector<std::string> cities1 = {"beijing", "shanghai", "xian"};
	    std::vector<std::string> cities2(std::move(cities1));
	    std::cout << "size:" << cities1.size() << std::endl;
	    std::cout << "size:" << cities2.size() << std::endl;
	    std::copy(cities2.begin(), cities2.end(), std::ostream_iterator<std::string>(std::cout, " "));
	
	    std::cout << std::endl;
	    std::cout << "---------------------" << std::endl;
	    std::string jimmy = "jimmy";
	    Person person1(1, jimmy);
	    std::string amao = "amao";
	    Person person2(2, amao);
	    std::vector<Person> p_vec1;
	    p_vec1.push_back(std::move(person1));
	    p_vec1.push_back(std::move(person2));
	    std::cout << person1 << std::endl;
	    for (auto& p : p_vec1) {
	        std::cout << p << std::endl;
	    }
	
	    std::vector<Person> p_vec2;
	    p_vec2 = std::move(p_vec1); //vector copy by std::move
	    std::cout << "p_vec1.size:" << p_vec1.size() << std::endl;
	    std::cout << "p_vec2.size:" << p_vec2.size() << std::endl;
	    for (auto& p : p_vec2) {
	        std::cout << p << std::endl;
	    }
	    return 0;
	}

##e.g. 3

	#include <iostream>
	#include <vector>
	#include <iterator>
	
	std::vector<std::string> cities_global = {"beijing_g", "shanghai_g", "xian_g"};
	
	std::vector<std::string> get_cities_local() {
	    std::vector<std::string> cities_local = {"beijing", "shanghai", "xian"};
	    return std::move(cities_local);
	}
	
	std::vector<std::string> get_cities_global() {
	    return std::move(cities_global); //vector copy by std::move
	}
	
	
	
	int main() {
	    std::vector<std::string> cities_local = get_cities_local();
	    std::copy(cities_local.begin(), cities_local.end(), std::ostream_iterator<std::string>(std::cout, " "));
	    std::cout << std::endl;
	
	    std::vector<std::string> cities_global_main = get_cities_global();
	    std::copy(cities_global_main.begin(), cities_global_main.end(), std::ostream_iterator<std::string>(std::cout, " "));
	    std::cout << std::endl;
	
	    std::cout << "cities_global.size:" << cities_global.size() << std::endl; 
	}
