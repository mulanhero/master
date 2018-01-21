#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <map>

template <class K, class V>
class MyContainer {
public:
    MyContainer() = default;

    void add_item(K k, V v) {
        if (table.find(k) == table.end()) {
            table[k] = v;
        } else {
            std::cout << k << " is already in it." << std::endl;
        }
    }

    void print() {
        for (auto& item : table) {
            std::cout << item.first << "," << item.second << std::endl;
        }
    }

private:
    std::map<K, V> table;
};

int main() {

    MyContainer<int, std::string> students;
    students.add_item(1, "caohaijun");
    students.add_item(2, "jimmy");
    students.add_item(2, "linjuan");
    

    students.print();

    return 0;
}
