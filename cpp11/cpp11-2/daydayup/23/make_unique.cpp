#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <utility>
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
    return 0;
}
