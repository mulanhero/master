#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::string str_array[] = {"beijing", "shanghai", "shenzhen", "11111111111111111111111", "a"};

    std::vector<std::string> str_vec(str_array, str_array + sizeof(str_array)/sizeof(str_array[0]));

    std::string to_remove = "beijing";
    std::vector<std::string>::iterator find_result = find(str_vec.begin(), str_vec.end(), to_remove);


    if (find_result != str_vec.end()) {
        *find_result = "wuhan";
        std::cout << "found, and revised" << std::endl;
        for (auto str : str_vec) {
            std::cout << str << std::endl;
        }

        
        str_vec.erase(find_result);
        std::cout << "found, and removed" << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }

    std::cout << "---------------" << std::endl;

    for (auto str : str_vec) {
        std::cout << str << std::endl;
    }

    std::cout << "size:" << str_vec.size() << std::endl;
    return 0;
}
