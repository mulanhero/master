#include <iostream>
#include <vector>


int main() {
    std::vector<std::pair<std::string, std::string>> person_phone;
    person_phone.push_back(std::make_pair<std::string, std::string>("jimmy", "1234"));
    //very cool!!!!
    person_phone.push_back({"cao", "5678"});

    for (auto& item : person_phone) {
        std::cout << item.first << "=" << item.second << std::endl;
    }
    return 0;
}
