#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::map<std::string, std::string> phone_books;

    phone_books.insert(std::make_pair<std::string, std::string>("cao","111"));
    phone_books.insert({"jimmy","2222"});

    for (auto& item : phone_books) {
        std::cout << item.first << "," << item.second << std::endl;
    }

    

    std::cout << std::boolalpha << std::is_sorted(phone_books.begin(), phone_books.end()) << std::endl;

    return 0;
}
