#include <utility>      // std::forward
#include <iostream>     // std::cout

//lvalue reference
void overloaded(const int& x) {
    std::cout << "[lvalue]";
}

//rvalue reference
void overloaded(int&& x) {
    std::cout << "[rvalue]";
}

//fn can accept either lvalue or rvalue
template <class T> 
void fn (T&& x) {
    //move makes lvalue/rvalue to rvalue
    overloaded(std::move(x));           

    //keep rvalue as rvalue, lvalue as lvalue, this "perfect forwarding"
    overloaded(std::forward<T>(x)); 
}

int main () {
    int lvalue = 0;

    std::cout << "calling fn with lvalue: ";
    fn (lvalue);
    std::cout << '\n';

    
    std::cout << "calling fn with rvalue: ";
    fn (std::move(lvalue));
    std::cout << '\n';

    return 0;
}
