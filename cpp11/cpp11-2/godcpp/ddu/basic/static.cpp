#include <iostream>
#include <atomic>

class MyClass {
public:
    static int64_t _s_id;

    MyClass(std::string name = "", int age = 0) : _name(name), _age(age) {
        ++_s_id;
    }

    int64_t get_s_id() {
        return _s_id;    
    }

private:
    //static std::atomic<int64_t> _s_id;
    std::string _name;
    int _age;
};

int64_t MyClass::_s_id = 0;
int main() {
    MyClass my1("jimmy", 2);
    MyClass my2("amao", 3);
    std::cout << my1.get_s_id() << std::endl;
    return 0;
}
