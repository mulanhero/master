#include <iostream>
#include <string>
#include <memory>

template <class T>
void swap (T& a, T& b) {
    T tmp(a);
    a = b;
    b = tmp;
}

template <class T> 
void swap_rvalue_ref(T& a, T& b) {
    //move is destructive read, it's better for vector
    //the param of move can be lvalue or rvale, 
    //it will return a rvalue without triggering a copy constructor
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}


class Person {
public:
    Person(std::string name, int age) : _name(name), _age(age) {}
private:
    std::string _name;
    int _age;
}; 

int main() {
    Person&& p = Person("cao", 35); //Person("cao", 35) is a temp, so must Person&&;
    Person p2("cao", 35);

    
}
