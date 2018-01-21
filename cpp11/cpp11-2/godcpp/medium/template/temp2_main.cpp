#include <iostream>
using namespace std;

template <typename Type>
class Poly {
private:
    Type base;
    Type height;
    public:
    Poly(Type b = 0, Type h = 0) :
            base(b), height(h) {
    }

    Type getArea() const {
        return base * height;
    }

    template <typename T>
    inline int compare(const T &t1, const T &t2) {
        if (t1 > t2) {
            return 1;
        } else if (t1 < t2) {
            return -1;
        } else {
            return 0;
        }
    }
};

int main() {
    int b1 = 2, h1 = 3;
    Poly<int> p1(b1, h1);
    int result = p1.compare(b1, h1);
    if (result > 0) {
        cout << b1 << ">" << h1 << endl;
    } else if (result < 0) {
        cout << b1 << "<" << h1 << endl;
    } else {
        cout << b1 << "=" << h1 << endl;
    }
    cout << "p1.getArea():" << p1.getArea() << endl;

    double b2 = 3.3, h2 = 2.2;
    Poly<double> p2(b2, h2);
    result = p2.compare(b2, h2);
    if (result > 0) {
        cout << b2 << ">" << h2 << endl;
    } else if (result < 0) {
        cout << b2 << "<" << h2 << endl;
    } else {
        cout << b2 << "=" << h2 << endl;
    }
    cout << "p2.getArea():" << p2.getArea() << endl;
    return 0;
}
