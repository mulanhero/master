#ifndef STUDENT_H_
#define STUDENT_H_

#include "Person.h"

class Student : public Person {
public:
    Student(std::string &name, int age, int grade) :
            Person(name, age), grade(grade) {
        std::cout << "in Student" << std::endl;
    }

    void print() {
        cout << "print in Student: " << endl;
        Person::print();   //call Base's print()
        cout << "grade:" << this->grade << endl;
    }

    friend std::ostream& operator<<(std::ostream &out, Student &s);

private:
    int grade;
};

std::ostream& operator<<(std::ostream &out, Student &s) {
    out << "name:" << s.getName() << ", age:" << s.getAge() << ", grade:" << s.grade;
    return out;
}

#endif /* STUDENT_H_ */
