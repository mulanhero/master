#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
template <class T>
int compare(T& t1, T& t2) {
    return t1 > t2 ? 1 : 0;
}

int main() {
    vector < string > v1;
    v1.push_back("aaaaaaaa");
    v1.push_back("zzzzzzzz");
    vector < string > v2;
    v2.push_back("yyyyyyyyy");
    v2.push_back("bbbbbbbb");

    v1.insert(v1.begin() + 1, v2.begin(), v2.end());
    for (auto str : v1) {
        cout << str << endl;
    }

    cout << "after reverse" << endl;
    reverse(v1.begin(), v1.end());
    for (size_t i = 0; i < v1.size(); i++) {
        cout << v1[i] << endl;
    }
    cout << "after sort" << endl;
    sort(v1.begin(), v1.end(), compare<string>);
    for (vector<string>::size_type i = 0; i < v1.size(); i++) {
        cout << v1.at(i) << endl;
    }
    cout << "after assgin" << endl;
    v1.assign(v2.begin(), v2.end());
    for (vector<string>::iterator it = v1.begin(); it != v1.end(); it++) {
        cout << *it << endl;
    }

    cout << "after erase" << endl;

    v1.erase(v1.end());
    for (size_t i = 0; i < v1.size(); i++) {
        cout << v1[i] << endl;
    }
    cout << "after =" << endl;
    v1 = v2;
    for (auto str : v1) {
        cout << str << endl;
    }
    if (v1 == v2) {
        cout << "v1 == v2" << endl;
    }
    cout << "after clear:" << endl;
    v1.clear();
    cout << "size : " << v1.size() << endl;

    return 0;
}

