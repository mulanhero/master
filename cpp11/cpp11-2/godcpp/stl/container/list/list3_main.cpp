#include <list>
#include <iostream>

using namespace std;

int main() {
    list < string > names;
    list<string>::iterator head = names.begin();

    if (head == names.end()) {
        cout << "names are null" << endl;
    } else {
        cout << "names are not null" << endl;
    }

    return 0;
}
