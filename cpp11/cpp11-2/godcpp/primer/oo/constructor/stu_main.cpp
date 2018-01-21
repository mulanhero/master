#include "Student.h"

int main() {
    std::string name("jimmy");
    Student s(name, 34, 12);
//	std::cout << s << std::endl;
    s.print();
    return 0;
}
