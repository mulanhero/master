#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    typedef std::unordered_map<std::string, std::string> hash_map_t;

    hash_map_t phone_book;
    phone_book["cao"] = "1234";
    phone_book["jimmy"] = "5678";

    phone_book.insert(hash_map_t::value_type("lin", "3211"));
    
    phone_book.insert(std::make_pair("juan", "3333"));

    for (auto& item : phone_book) {
        std::cout << item.first << "," << item.second << std::endl;
    }

    bool sorted_flag = std::is_sorted(phone_book.begin(), phone_book.end());
    std::cout << sorted_flag << std::endl;

    std::cout << phone_book["mumu"] << std::endl;
    auto it = phone_book.find("mumu");
    std::cout << std::boolalpha <<  (it != phone_book.end()) << std::endl;
    return 0;
}
