#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef struct square {
    int id;
    int length;
    int width;

    const bool operator<(square &s) const {
        if (s.id != id) {
            return id < s.id;
        } else {
            if (length != s.length) {
                return length < s.length;
            } else if (width != s.width) {
                return width < s.width;
            } else {
                return false;
            }
        }
    }

} square_t;

int main() {

    square_t s1;
    s1.id = 3;
    square_t s2;
    s2.id = 4;

    if (s2 < s1) {
        cout << "s2 < s1" << endl;
    } else {
        cout << "s2 > s1" << endl;
    }

    return 0;
}
