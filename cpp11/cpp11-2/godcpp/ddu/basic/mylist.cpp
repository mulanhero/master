#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class MyList {
private:
    static const int _SIZE = 5;
    int array[_SIZE];

public:
    MyList() {
        for (size_t i = 0; i < _SIZE; i++) {
            array[i] = 0;
        }
    }

    int& operator[](int i) {
        assert(i >= 0 && i < _SIZE);
        return array[i];
    }
    void print() {
        for (size_t i = 0; i < _SIZE; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    MyList list;
    list.print();
    list[3] = 5;
    list.print();
    return 0;
}
