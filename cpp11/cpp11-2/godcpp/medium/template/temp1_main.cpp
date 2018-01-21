#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <typename T>
inline std::string toString(T tx) {
    ostringstream oss;
    oss << tx;
    return oss.str();
}

template <typename T>
inline bool fromString(const string &str, T &tx) {
    istringstream iss(str);
    return (iss >> tx) ? true : false;
}

int main() {
    //-----------------------------
    string s1(toString(314));
    cout << s1 << endl;
    string s2(toString('A'));
    cout << s2 << endl;
    string s3(toString(6.7));
    cout << s3 << endl;
    //-----------------------------
    string str("3.1415");
    double myPi;
    if (fromString(str, myPi)) {
        cout << myPi << endl;
    }
}
