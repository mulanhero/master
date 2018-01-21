#include <iostream>
#include <vector>
void add(std::string&& r_ref) {
    r_ref.append(", hello");
}
int main() {
    std::string name;
    name = "cao";
    std::string& lvalue_ref = name;
    add(std::move(lvalue_ref));
    //the content of lvalue_ref is cleared by std::string's move_constructor
    //it's really cool in vector
    std::string constructor_name(std::move(lvalue_ref));
    std::cout << name << std::endl;
    std::cout << constructor_name << std::endl;
    return 0;
}
