#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iterator>
int main() {
    std::unique_ptr<std::vector<std::string>> vec_ptr(new std::vector<std::string>(3));
    vec_ptr->push_back("shanghai");
    vec_ptr->push_back("beijing");
    vec_ptr->push_back("xian");

    std::unique_ptr<std::vector<std::string>> vec_ptr2;
    
    std::swap(vec_ptr, vec_ptr2);

    for (auto it = vec_ptr2->begin(); it != vec_ptr2->end(); it++) {
        std::cout << *it << std::endl;
    }

    if (!vec_ptr && vec_ptr2) {
        std::cout << "!vec_ptr && vec_ptr2" << std::endl;
    }
    
    //-----------------------------------
    std::vector<std::string> src_vec = {"shanghai", "beijing"};
    std::vector<std::string> target_vec;
    std::swap(src_vec, target_vec);
    std::copy(target_vec.begin(), target_vec.end(), std::ostream_iterator<std::string>(std::cout, "\t"));
    std::cout << std::endl;
    std::cout << "src_vec.size():" << src_vec.size() << std::endl;
    return 0;
}
