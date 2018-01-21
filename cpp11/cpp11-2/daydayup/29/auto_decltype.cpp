#include <string>
#include <iostream>
class MyInt;
class MyString;

class MyInt {
public:
    MyInt(int v) : _value(std::move(v)) {}

    int get_value() const {
        return _value;
    }

    friend std::ostream& operator<<(std::ostream& out, const MyInt& my) {
        out << my._value;
        return out;
    } 

    MyInt operator+(const MyString& str);
private:
    int _value;
};


class MyString {
public:
    MyString(std::string str) : _str(std::move(str)) {}

    std::string get_str() const {
        return _str;
    }

    friend std::ostream& operator<<(std::ostream& out, const MyString& my) {
        out << my._str;
        return out;
    } 

    MyString operator+(const MyInt& i);
private:
    std::string _str;
};


MyInt MyInt::operator+(const MyString& str) {
    return _value + std::stoi(str.get_str());
}


MyString MyString::operator+(const MyInt& i) {
    std::string tmp(_str);
    return tmp + std::to_string(i.get_value());
}


template <class T1, class T2, class RESULT> 
RESULT concat1(T1& t1, T2& t2) {
    return t1 + t2;
}

template <class T1, class T2>
auto concat2(T1& t1, T2& t2) -> decltype(t1+t2) {
    return t1 + t2;
}


int main() {
    MyString tmp_str("1");
    MyInt tmp_int(9);
    std::cout << concat1<MyString, MyInt, MyString>(tmp_str, tmp_int) << std::endl;
    std::cout << concat2<MyString, MyInt>(tmp_str, tmp_int) << std::endl;
    return 0;
}
