#include <iostream>
#include <memory>

class Person {
public:
    Person(std::string id) {
        _id_ptr = new std::string(id);
    } 

    ~Person() {
        std::cout << "delete " << std::endl;
        delete _id_ptr; 
    }


    friend std::ostream& operator<< (std::ostream& out, const Person& p) {
        out << "id:" << *p._id_ptr;
        return out;
    }

private:
    std::string*  _id_ptr;
};

int main() {
    std::unique_ptr<Person> tmp(new Person("0002"));
    std::unique_ptr<Person> person_ptr = std::move(tmp); 
//    std::shared_ptr<Person> person_ptr = std::make_shared<Person>("0002");
    std::cout << *person_ptr << std::endl; 
    person_ptr.reset();
    std::cout << "to check that destructor will be before this output" << std::endl;
}
