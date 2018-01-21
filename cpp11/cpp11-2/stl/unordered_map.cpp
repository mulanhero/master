#include <unordered_map>
#include <iostream>

int main() {
    std::unordered_map<int, std::string> cities(10);
    cities.emplace(10, "beijing");
    cities.emplace(20, "shanghai");

    for (auto& it : cities) {
        std::cout << it.first << ":" << it.second << std::endl;
    }
}
