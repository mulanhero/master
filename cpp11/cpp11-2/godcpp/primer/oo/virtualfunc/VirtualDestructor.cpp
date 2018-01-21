#include <iostream>

using namespace std;

/*
 whenever you are dealing with inheritance, you should make your destructors virtual.
 */
class Base {
public:
    virtual ~Base() {
        cout << "Calling ~Base() " << endl;
    }
};

class Derived : public Base {
private:
    int *array;
    public:
    Derived(int size) {
        array = new int[size];
    }
    virtual ~Derived() {
        cout << "Calling ~Derived" << endl;
        delete[] array;
    }
};

int main() {
    Derived *derived = new Derived(5);
    Base *basePtr = derived;
    delete basePtr;
    return 0;
}
