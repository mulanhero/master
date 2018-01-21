#include <iostream>
#include <stack>

int main() {
    std::stack<int> my_stk;

    my_stk.push(1);
    my_stk.push(2);
    my_stk.push(3);

    std::cout << my_stk.top() << std::endl;
    my_stk.pop();

    std::cout << my_stk.top() << std::endl;

    return 0;
}
