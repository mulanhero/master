#include <map>
#include <iostream>
#include <string>
#include <utility>

class Complicated {
public:
    Complicated(int i = 0, double d = 0.0, std::string str = "") 
        : _i(i), _d(d), _str(str) {
    }
 
private:
    int _i;
    double _d;
    std::string _str;
};

int main() {
    std::map<int, Complicated> m;
    int anInt = 4;
    double aDouble = 5.0;
    std::string aString = "C++";

     m.insert(std::make_pair(4, Complicated(anInt, aDouble, aString))); 

     std::cout << m.count(5) << std::endl;
     Complicated c(anInt, aDouble, aString);
     m[5] = c;

     std::cout << m.size() << std::endl;
    return 0;
}
