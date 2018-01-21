#include <iostream>
#include <vector>
#include <string>

struct Item {
    int key;
    std::string value;
};

int main() {
    std::vector<Item> items = {{3, "ok"}, {4, "okey"}};
    std::cout << items.size() << std::endl;

    for (auto& i : items) {
        std::cout << i.key << "," << i.value << std::endl;
    }
    return 0;
}
