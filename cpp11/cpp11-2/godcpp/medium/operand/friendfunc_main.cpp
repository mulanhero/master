#include <iostream>

class Cent {
public:
    Cent(int num) :
            num(num) {
    }
    ~Cent() {
    }

    friend Cent operator+(Cent &c1, Cent &c2) {
        return Cent(c1.num + c2.num);
    }

    friend Cent operator+(Cent &c1, int num) {
        return Cent(c1.num + num);
    }

    friend Cent operator+(int num, Cent &c1) {
        return c1 + num;
    }

    int getCent() {
        return this->num;
    }

private:
    int num;
};

int main() {
    using namespace std;
    Cent c1(2);
    Cent c2(3);
    Cent c3 = c1 + c2;
    cout << "c3:" << c3.getCent() << endl;

    Cent c4 = c1 + 3;
    cout << "c4:" << c4.getCent() << endl;

    Cent c5 = 3 + c1;
    cout << "c5:" << c5.getCent() << endl;
    return 0;
}
