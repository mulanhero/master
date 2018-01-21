#include <string>
#include <iostream>

using namespace std;
int main() {
// ------------------length() / size()
//	size_type string::length() const
//	size_type string::size() const
    string number("0123456789");
    cout << "length:" << number.length() << endl;
    cout << "length:" << number.size() << endl;
//---------------------empty()
    cout << "if empty:" << (number.empty() ? "true" : "false") << endl;
    string emptyStr;
    cout << "if empty:" << (emptyStr.empty() ? "true" : "false") << endl;

//---------------------capacity, reserve
//	void string::reserve()
//	void string::reserve(size_type unSize)
    string sixteen("0123456789abcdef");
    cout << "sixteen's length: " << sixteen.length() << endl;
    cout << "sixteen's capacity:" << sixteen.capacity() << endl;
    sixteen.reserve(200);
    cout << "sixteen's length: " << sixteen.length() << endl;
    cout << "sixteen's capacity:" << sixteen.capacity() << endl;
    sixteen.reserve();
    cout << "sixteen's length: " << sixteen.length() << endl;
    cout << "sixteen's capacity:" << sixteen.capacity() << endl;

    return 0;
}
