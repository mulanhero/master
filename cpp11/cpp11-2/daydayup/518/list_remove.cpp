#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

int main() {
    std::list<int> mylist = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    //erase 
    auto it = std::find(mylist.begin(), mylist.end(), 4);
    if (it != mylist.end()) {
        mylist.erase(it);
    }
    std::copy(mylist.begin(), mylist.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    mylist.erase(std::remove(mylist.begin(), mylist.end(), 2), mylist.end());
    std::copy(mylist.begin(), mylist.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "front is:" << mylist.front() << ", back is:" << mylist.back() << std::endl;
    mylist.pop_front();
    std::copy(mylist.begin(), mylist.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    mylist.pop_back();
    std::copy(mylist.begin(), mylist.end(), std::ostream_iterator<int>(std::cout, " "));
    
}
