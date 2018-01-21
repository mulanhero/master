#include <iostream>
using namespace std;

int main() {
    int num = 10;
    int* const p = &num;
    cout << "*p:" << *p << endl;
    num = 20;
    cout << "*p:" << *p << endl;
    int another = 20;
    //p = &another;  // p is const to &num, is not changable

    const int *cp = &num;
    cout << "*cp:" << *cp << endl;
    num = 30;
    cout << "*cp:" << *cp << endl;
    //*cp = 40;  //for cp, he believe what he points to can not changable

    const int * const ccp = &num;
    num = 50;
//	ccp = &another;  //for ccp, he can not point to other
//	*ccp = 100;			//for cpp, he believe what the points to can not changable
    cout << "*cp:" << *cp << endl;

}
