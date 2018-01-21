#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <iostream>
using namespace std;

class Animal {
public:
    Animal(string &name, int age) :
            name(name), age(age) {
    }
    virtual ~Animal() {
    }

    virtual const string speak() {
        return string("???");
    }

private:
    string name;
    int age;
};

class Dog : public Animal {
public:
    Dog(string &name, int age) :
            Animal(name, age) {
    }
    virtual ~Dog() {
    }

    virtual const string speak() {
        return string("WoW");
    }
};

void report(Animal &animal) {
    cout << animal.speak() << endl;
}

int main() {

    string name("ADog");
    Dog dog(name, 2);
    Animal &animal = dog;
    report(animal);
    return 0;
}

#endif /* ANIMAL_H_ */
