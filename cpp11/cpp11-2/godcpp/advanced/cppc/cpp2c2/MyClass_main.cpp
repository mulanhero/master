#include "MyClass.h"

using namespace std;
using namespace libyarn;

int main() {
    std::string name("Jimmy");
    MyClass my(name);
    cout << my.getName() << endl;
    return 0;
}
