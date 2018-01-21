#include <iterator>
#include <iostream>
#include <deque>
#include <algorithm>


void print(std::deque<int>& first_dq, std::deque<int>& second_dq) {
    std::copy(first_dq.begin(), first_dq.end(), 
            std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::copy(second_dq.begin(), second_dq.end(), 
            std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

void print(std::deque<int>& dq) {
    std::copy(dq.begin(), dq.end(),
            std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

const size_t SIZE = 5;
int main() {
    std::deque<int> first_dq;
    std::deque<int> second_dq;
    std::deque<int> third_dq(SIZE * 2);

    for (size_t i = 0; i < SIZE; ++i) {
        first_dq.push_back(i);
        second_dq.push_front(i);
    }
    print(first_dq, second_dq);

    std::merge(first_dq.begin(), first_dq.end(), 
            second_dq.begin(), second_dq.end(), 
            third_dq.begin());
    print(first_dq, second_dq);
    print(third_dq);


    std::sort(third_dq.begin(), third_dq.end());
    print(third_dq);

    auto end = std::unique(third_dq.begin(), third_dq.end());
    print(third_dq);
    third_dq.erase(end, third_dq.end());
    print(third_dq);

    return 0;
}

