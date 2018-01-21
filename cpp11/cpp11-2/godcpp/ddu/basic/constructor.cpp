/*
 * constructor.cpp
 *
 *  Created on: 2015年3月2日
 *      Author: caohaijun
 */
#include<iostream>
class Person {
public:
    Person():_age(0) {
    }

    Person(std::string name, int age) : _name(name), _age(age) {}

    Person(const Person& p) {
        std::cout << "in copy constructor" << std::endl;
        _name = p._name;
        _age = p._age;
    }

    Person& operator=(const Person& p) {
        std::cout << "in operator=" << std::endl;
        if (&p == this) {
            return *this;
        }
        _name = p._name;
        _age = p._age;
    }

    virtual ~Person() = default;

    void set_age(int age) {
        _age = age;
    }

    void print() {
        std::cout << "name:" << _name << ", _age:" << _age << std::endl;
    }
private:
    std::string _name;
    int _age;
};

class FamilyByValue {
public:
    /*
     * will call two times of copy_contructor
     * 1) when transfer function's parameter by value
     * 2) when initializa Person _mother(mother)
     */
//    explicit FamilyByValue(Person mother) : _mother(mother)  {
//    }

    /*
     * 1. will call copy_constructor when tranfer function's parameter by value
     * 2. will call operator= when '_mother = mother', because _mother's memory have been allocated
     */
    explicit FamilyByValue(Person mother) {
        _mother.print();
        _mother = mother;
    }

    void print() {
        _mother.set_age(12);
        _mother.print();
    }
private:
    Person _mother;
};



class FamilyByRef {
public:
    /*
     * only one time of copy_constructor in '_mother(mother)'
     * because function's parameter is by ref, no copy_constructor here
     */
//    explicit FamilyByRef(const Person& mother) : _mother(mother)  {
//    }


    /*
     * only one time of operator= in '_mother=mother'
     * because function's parameter is by ref, no copy_constructor here
     */
    explicit FamilyByRef(const Person& mother) {
        _mother.print();
        _mother = mother;
    }

    void print() {
        _mother.set_age(12);
        _mother.print();
    }
private:
    Person _mother;
};

class FamilyRefByRef {
public:
    /*
     * no copy_constructor and operator= because pure ref
     */
    explicit FamilyRefByRef(Person& mother) : _mother(mother)  {
    }

    /*
     * Note: it is disallowed, because ref must be initialized when declared!!!!
     */
//    explicit FamilyRefByRef(Person& mother) {
//        _mother = mother;
//    }

    void print() {
        _mother.set_age(12);
        _mother.print();
    }
private:
    Person& _mother;
};


int main() {
    Person m("mama", 31);
//    FamilyByValue f(m);
//    FamilyByRef f(m);
    FamilyRefByRef f(m);
    f.print();
    m.print();
    return 0;
}
