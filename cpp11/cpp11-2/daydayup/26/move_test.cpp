#include <memory>
#include <iostream>
#include <vector>

class Person {
public:
    Person(std::string& name, int age) : _name(std::move(name)), _age(age) {}
    friend std::ostream& operator<<(std::ostream& out, const Person& p) {
        out << p._name << "," << p._age << std::endl;
        return out;
    }
private:
    std::string _name;
    int _age;
};


int main() {
    std::string tmp_name = "jimmy";
    Person p(tmp_name, 35);
    std::cout << p;
    std::cout << "origal tmp_name:" << tmp_name << std::endl;
    return 0;
}

//notice:
//the output would be:

//jimmy,35
//origal tmp_name:

//it's interesting, because in contructor, the param is a lvalue ref(std::string& name)
//after std::move(name), which name will be rvalue ref, after std::string's move_constructor, the rvalue ref's content will clear
//the real content is cleared by string's move constructor
