/*
 * Teacher.h
 *
 *  Created on: Jul 15, 2014
 *      Author: jcao
 */

#ifndef TEACHER_H_
#define TEACHER_H_

#include "Person.h"
#include "Employee.h"

using namespace std;

class Teacher : public Person, public Employee {
private:
public:
    Teacher(string &name, int age, string &sex, int salary, long personId,
            long employId) :
            Person(name, age, sex, personId), Employee(employId, salary) {
    }

    friend ostream& operator<<(ostream& out, Teacher &t);
};

ostream& operator<<(ostream& out, Teacher &t) {
    out << "name:" << t.getName() << ", age:" << t.getAge() << ", sex:"
            << t.getSex() << ", salary:" << t.getSalary() << ", personId:"
            << t.Person::getId() << ", employId:" << t.Employee::getId(); //to distinct getId() in Person and Employee
    return out;
}

#endif /* TEACHER_H_ */
