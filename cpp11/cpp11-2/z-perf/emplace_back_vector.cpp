#include <iostream>
#include <vector>

class Person {
public:
    Person(int age, std::string name) : _age(age), _name(name) {}

    friend std::ostream& operator<< (std::ostream& out, Person& p) {
        out << "age:" << p._age << ", " << "name:" << p._name;
        return out;
    }
private:
    int _age;
    std::string _name;

};
int main() {
    std::vector<std::pair<int, std::string>> cities;
    cities.push_back(std::make_pair(10, std::string("beijing")));
    cities.emplace_back(20, std::string("shanghai"));

    for (auto& it : cities) {
        std::cout << it.first << ":" << it.second << std::endl;
    }

    //---------------------------------------
    std::vector<Person> persons;
    persons.push_back(Person(1, "jimmy"));
    persons.emplace_back(2, "amao");
    persons.emplace(3, "niahao");

    for (auto& p : persons) {
        std::cout << p << std::endl;
    }
    return 0;
}
