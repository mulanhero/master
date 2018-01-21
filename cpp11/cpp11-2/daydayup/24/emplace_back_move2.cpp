#include <iostream>
#include <vector>
#include <string>

class Person {
public:
    Person(std::string name, int age = 0) : _name(std::move(name)), _age(age) {
        std::cout << "in constructor " << std::endl;
    }

    Person(const Person& other) {
        copy_member(other);
        std::cout << "in copy contructtor" << std::endl;
    }

    Person(Person&& other) {
        *this = std::move(other);
        std::cout << "in move copy constructor " << std::endl;
    }

    Person& operator=(Person&& other) {
        if (this != &other) {
            _name = std::move(other._name);
            _age = other._age;

            other._age = 0;
        }
    }

    Person& operator=(const Person& other) {
        if (this == &other) {
            return *this;
        }
        copy_member(other);

        std::cout << " in operator= constructor " << std::endl;
        return *this;
    }

    virtual ~Person() = default;


    friend std::ostream& operator<<(std::ostream& out, const Person& p) {
        std::cout << "name:" << p._name << ", age" << p._age << std::endl;
    }

private:
    void copy_member(const Person& other) {
        _name = std::move(other._name);
        _age = other._age;
    }

    std::string _name;
    int _age;
};


int main() {
    std::vector<Person> vec;
    vec.emplace_back("cao", 33);
   // Person p("jimmy", 34);
   // vec.push_back(p);
    vec.push_back(Person("jimmy", 34));

    for (auto& p : vec) {
        std::cout << p ;
    }

    return 0;
}
