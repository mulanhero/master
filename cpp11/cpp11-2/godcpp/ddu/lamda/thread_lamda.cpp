#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <thread>

class Person {
public:
    Person(std::string name="", int age=0, int sum=0) : _name(name), _age(age), _sum(sum) {}

    void run(int start, int end) {
        std::thread t = std::thread([this, start, end]() {
                    int tmp = start;
                    for (; tmp < end; tmp++) {
                        _sum += tmp;
                    }
                });
        t.join();
    }

    void print() {
        std::cout << "sum :" << _sum << std::endl;
    }

private:
    std::string _name;
    int _age;
    int _sum;
};


int main() {
    std::string name = "jimmy";
    Person p(name, 35, 0);
    p.run(1, 9);
    p.print();

    return 0;
}
