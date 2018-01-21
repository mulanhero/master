#include <iostream>
#include <vector>
#include <utility>
#include <string>

class  Person {
public:
    std::string name;
    int age;
    bool sex;
    Person(std::string _name = "", int _age = 0, bool _sex = true) 
        : name(_name), age(_age), sex(_sex) {}
};


int main() {
    /* ---------------------------------------------------------------------- */
    std::vector<std::pair<size_t, Person>> table;
    Person p;
    p.name = "jimmy";
    p.age = 35;
    p.sex = true;
    table.push_back(std::make_pair(1, p));
    //emplace_back 
    table.emplace_back(std::make_pair(2, p));

    for (auto& item : table) {
        std::cout << item.first << ", " << item.second.name 
            << " " << item.second.age << " " << item.second.sex << std::endl;
    }

    
    /* ---------------------------------------------------------------------- */
    std::vector<Person> v2;
    v2.push_back(p);
    //very cool
    v2.emplace_back("amao", 33, false);
    for (auto& e : v2) {
        std::cout << e.name << " " << e.age << " " << e.sex << std::endl;
    }
    return 0;
}
