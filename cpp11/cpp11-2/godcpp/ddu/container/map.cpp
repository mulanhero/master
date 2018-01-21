#include <iostream>
#include <string>
#include <map>
#include <algorithm>


int main() {
    std::map<std::string, size_t> word_count;
    word_count["beijing"] = 1;
    word_count["shanghai"] = 2;
    word_count["shenzhen"] = 3;
    word_count["wuhan"] = 4;

    std::cout << "size:" << word_count.size() << std::endl;
    //std::map<std::string, size_t>::iterator it = word_count.find("beijing");
    auto it = word_count.find("beijing");
    if (it != word_count.end()) {
        std::cout << it->first << ", " << it->second << std::endl;
        word_count.erase(it);
        std::cout << "after erase, size:" << word_count.size() << std::endl; 
    }

    std::string to_count = "shanghai";
    auto sum = word_count.count(to_count);
    std::cout << "sum:" << sum << std::endl;
    

    //for (std::map<std::string, size_t>::iterator it = word_count.begin(); it != word_count.end(); ++it) {
    for (auto it = word_count.begin(); it != word_count.end(); ++it) {
        std::cout << it->first << ", " << it->second << std::endl;
    }
   /* 
    for (auto const & it : word_count) {
        std::cout << it->first << ", " << it->second << std::endl;
    }
    */
        
    return 0;
}
