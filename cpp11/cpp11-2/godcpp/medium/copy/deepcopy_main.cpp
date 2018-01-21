#include <iostream>

using namespace std;

class Address {
public:
    Address(const string & location, int postcode) :
            location(location), postcode(postcode) {
    }

    ~Address() {
    }

    void setLocation(const string & location) {
        this->location = location;
    }

    string getLocation() {
        return this->location;
    }

    void setPostcode(int postcode) {
        this->postcode = postcode;
    }

    int getPostcode() {
        return this->postcode;
    }

    friend ostream& operator<<(ostream &out, Address &addr);

private:
    string location;
    int postcode;
};

ostream& operator<<(ostream &out, Address &addr) {
    out << "location:" << addr.location << ", postcode:" << addr.postcode;
    return out;
}

//-----------------------------
class Person {
public:
    Person() {
    }
    Person(Address *addr, string &name, int age) :
            name(name), age(age) {
        this->addr = addr;
    }

    ~Person() {
        delete (this->addr);
    }

    //copy constructor
    /*
     There are three general cases where the copy constructor is called instead of the assignment operator:
     When instantiating one object and initializing it with values from another object.
     When passing an object by value.
     When an object is returned from a function by value.
     */
    Person(const Person & p) {
        if (p.addr) {
            this->addr = new Address(p.addr->getLocation(), p.addr->getPostcode());
        } else {
            this->addr = 0;
        }
        this->name = p.name;
        this->age = p.age;
    }

    //assignment : deep copy
    Person & operator=(const Person & p) {
        //1. check if the p = p
        if (this == &p) {
            return *this;
        }
        //2. prevent memory leak
        delete (this->addr);

        //3. deep copy
        if (p.addr) {
            this->addr = new Address(p.addr->getLocation(), p.addr->getPostcode());
        } else {
            this->addr = 0;
        }
        //4. shallow copy non-dynamic-allocated (in heap) object
        this->name = p.name;
        this->age = p.age;
        return *this;
    }

    friend ostream& operator<<(ostream &out, Person &p);

private:
    Address *addr;
    string name;
    int age;
};

ostream& operator<<(ostream &out, Person &p) {
    out << "addr:" << *(p.addr) << ", name:" << p.name << ", age:" << p.age;
    return out;
}

int main() {
    string location1("Shanghai, China");
    int postcode = 200000;

    Address *addr1 = new Address(location1, postcode);
    string name1("jimmy");
    Person jimmy(addr1, name1, 34);

    {
        //copy constructor
        Person jimmy2 = jimmy;
        cout << jimmy2 << endl;

        //=
        Person jimmy3;
        jimmy3 = jimmy;
        cout << jimmy3 << endl;

        //Note: ~Person() will be invoked when the block finished
    }

    cout << jimmy << endl;

    //Note: addr1 has been freed in ~Person()
//	delete addr1;

    return 0;
}
