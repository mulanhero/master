#include <iostream>
#include <queue>

int main() {
    std::queue<int> my_q;
    my_q.push(1);
    my_q.push(2);
    my_q.push(3);

    std::cout << my_q.front() << std::endl;
    my_q.pop();

    std::cout << "size:" << my_q.size() << std::endl;

    std::cout <<  my_q.front() << std::endl;
    
    std::cout << my_q.back() << std::endl;
    return 0;
}
