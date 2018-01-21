#include <string>
#include <iostream>

using namespace std;

class PureAnimal {
public:
    PureAnimal(string name) :
            name(name) {
    }

    string getName() {
        return name;
    }

    virtual const char* speak() = 0; //pure virtual function

private:
    string name;
};

class Dog : public PureAnimal {
public:
    Dog(string name) :
            PureAnimal(name) {
    }

    virtual const char* speak() {
        return "WoW";
    }
};

int main() {
    string name("coolDog");
    Dog dog(name);
    cout << dog.getName() << ":" << dog.speak() << endl;
    return 0;
}
