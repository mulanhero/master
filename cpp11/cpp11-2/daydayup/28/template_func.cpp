#include <iostream>
#include <type_traits>

#include <typeinfo>
#include <memory>

struct Person {
    std::string name;
    int age;
};

struct Student : public Person {
    std::string grade;
};


template <class T> 
std::unique_ptr<T> get() {
    std::unique_ptr<T> tmp_ptr(new T());
    tmp_ptr->name = "person";
    tmp_ptr->age = 1;
    std::cout << typeid(*tmp_ptr).name() << std::endl;
    return std::move(tmp_ptr);
}


int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_base_of<Person, Student>::value << std::endl;
    

    std::unique_ptr<Person> p = get<Person>();
    std::cout << p->name << ", " << p->age << std::endl;

    p = get<Student>();
    std::cout << p->name << ", " << p->age << std::endl;
    return 0;
}
