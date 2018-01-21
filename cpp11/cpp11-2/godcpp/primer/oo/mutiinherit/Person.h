/*
 * Person.h
 *
 *  Created on: Jul 15, 2014
 *      Author: jcao
 */

#ifndef PERSON_H_
#define PERSON_H_

#include <iostream>

using namespace std;

class Person {
private:
    string name;
    int age;
    string sex;
    long id;
    public:
    Person() {
    }

    ~Person() {
    }

    Person(string &name, int age, string &sex, long id) :
            name(name), age(age), sex(sex), id(id) {
    }

    string getName() {
        return this->name;
    }

    int getAge() {
        return this->age;
    }

    string getSex() {
        return this->sex;
    }

    long getId() {
        return this->id;
    }
};

#endif /* PERSON_H_ */
