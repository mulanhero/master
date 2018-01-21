#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class T>
inline string toStr(T& t) {
    ostringstream oss;
    oss << t;
    return oss.str();
}

template <typename T>
inline int fromStr(string& str, T& t) {
    istringstream iss(str);
    return iss >> t ? 0 : 1;
}

int main() {
    int value = 22;
    string str = toStr(value);
    cout << str << endl;

    int result;
    fromStr(str, result);
    cout << result << endl;

    return 0;
}
