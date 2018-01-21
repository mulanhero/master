/*
 * Employee.h
 *
 *  Created on: Jul 15, 2014
 *      Author: jcao
 */

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

class Employee {
private:
    long id;
    int salary;

public:
    Employee() {
    }
    ~Employee() {
    }
    Employee(long id, int salary) :
            id(id), salary(salary) {
    }

    int getSalary() {
        return this->salary;
    }

    long getId() {
        return this->id;
    }
};

#endif /* EMPLOYEE_H_ */
