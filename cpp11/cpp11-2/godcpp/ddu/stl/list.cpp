#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>

void print_list(std::list<std::string>& city_list) {
    std::cout << std::endl;
    std::copy(city_list.begin(),city_list.end(), std::ostream_iterator<std::string>(std::cout, " "));
}

int main() {
    std::vector<std::string> city_vec = {"beijing", "wuhan", "xian", "shaihai", "shenzhen"};

    std::list<std::string> city_list(city_vec.begin(), city_vec.end());
    print_list(city_list);

    city_list.pop_front();
    print_list(city_list);
    

    city_list.front() = "wuhaner";
    print_list(city_list);

    city_list.sort();

    print_list(city_list);
    return 0;
}
