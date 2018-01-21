#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


int main() {
    std::vector<int>  vec1 = {1, 2, 3, 4, 5};

    std::transform(vec1.begin(), vec1.end(), vec1.begin(), [](int i)->int {return 2 * i;});
    std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::for_each(vec1.begin(), vec1.end(), [](int& i){ i *= 2;} );
    std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
