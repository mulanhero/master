#include <iostream>
#include <string>
#include <cassert>
using namespace std;
class matrix {
private:
    static const int _SIZE = 4;
    int array[_SIZE][_SIZE];
    public:
    matrix() {
        for (size_t i = 0; i < _SIZE; i++) {
            for (size_t j = 0; j < _SIZE; j++) {
                array[i][j] = 0;
            }
        }
    }

    int& operator()(int i, int j) {
        assert(i >= 0 && i < _SIZE);
        assert(j >= 0 && j < _SIZE);
        return array[i][j];
    }

    void print() {
        for (size_t i = 0; i < _SIZE; i++) {
            for (size_t j = 0; j < _SIZE; j++) {
                cout << i << ", " << j << ": " << array[i][j] << endl;
            }
        }
    }
};

int main() {
    matrix m;
    m.print();

    cout << "-----------------" << endl;
    m(1, 1) = 5;
    m.print();
    return 0;
}
