#include <vector>
#include <iostream>
#include <string>

int main() {
    std::vector<std::string> cities;
    cities.assign(1, "beijing");
    cities.push_back("shanghai");
    cities.push_back("xian");
    cities.push_back("wuhan");
    //assign will clear all above and push_back
//    cities.assign(2, "xian");

    for(auto& city : cities) {
        std::cout << city << std::endl;
    }

    std::cout << std::endl;

    std::vector<std::string> cities2;
    cities2.assign(cities.begin()+1, cities.end());
    for (auto& city : cities2) {
        std::cout << city << std::endl;
    }
    return 0;
}
