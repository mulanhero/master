#include <iostream>
#include <list>

using namespace std;
int main() {
    int sum[] = { 1, 2, 3, 4, 5 };
    list<int> sumList(sum, sum + 4);
    sumList.remove(3);
    for (list<int>::iterator it = sumList.begin(); it != sumList.end(); it++) {
        cout << *it << endl;
    }
}
