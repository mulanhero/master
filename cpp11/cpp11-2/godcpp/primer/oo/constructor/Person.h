#ifndef PERSON_H_
#define PERSON_H_

#include <iostream>

using namespace std;

class Person {
public:
    Person(std::string &name, int age) :
            name(name), age(age) {
    }

    std::string getName() {
        return this->name;
    }

    int getAge() {
        return this->age;
    }

    void print() {
        cout << "name:" << this->name << ", age:" << this->age << endl;
    }

    friend std::ostream& operator<<(std::ostream &out, Person &p);
    private:
    std::string name;
    int age;
};

std::ostream& operator<<(std::ostream &out, Person &p) {
    out << "name:" << p.name << ", age:" << p.age;
    return out;
}

#endif /* PERSON_H_ */
