#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
int comp(T& t1, T& t2) {
    return t1 > t2 ? 1 : 0;
}

int main() {
    vector < string > v1;
    v1.push_back(string("aaaaaaaa"));
    v1.push_back(string("zzzzzzzzzzz"));

    vector < string > v2;
    v2.push_back(string("cccccccccc"));
    v2.push_back(string("bbbbbb"));

    v1.insert(v1.begin() + 1, v2.begin(), v2.end());

    cout << "size:" << v1.size() << endl;

    sort(v1.begin(), v1.end(), comp<string>);

    for (auto str : v1) {
        cout << str << endl;
    }

    cout << "--------------------" << endl;

    reverse(v1.begin(), v1.end());
    for (vector<string>::size_type i = 0; i < v1.size(); i++) {
        cout << v1[i] << endl;
    }

    cout << "--------------------" << endl;

    v1.erase(v1.begin(), v1.begin() + 2);
    for (size_t i = 0; i < v1.size(); i++) {
        cout << v1.at(i) << endl;
    }

    cout << "-----------1---------" << endl;
    v1.assign(v2.begin(), v2.end());
    for (vector<string>::iterator it = v1.begin(); it != v1.end(); it++) {
        cout << *it << endl;
    }
    cout << "-------2-------------" << endl;

    cout << "--------------------" << endl;

    v1.clear();
    cout << "size :" << v1.size() << endl;

    return 0;
}
