#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iomanip>


class Archive {
public:
    template <class T> 
    size_t size() {
        return sizeof(T);
    }
};

int main() {
    Archive ar;
    size_t sz = ar.template size<int>();
    std::cout << sz << std::endl;
    size_t sz2 = ar.size<int>();
    std::cout << sz2 << std::endl;

    return 0;
}
