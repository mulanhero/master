#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>


bool longer_than_6(std::string str) {
    return str.size() > 6 ? true : false;
}


class LongThan {
public:
    LongThan(size_t threshold = 0) : _threshold(threshold) {}

    bool operator()(std::string str) { 
        return str.size() > _threshold ? true : false;
    }
private:
    size_t _threshold;

};

int main() {
    std::vector<std::string> str_vec = {"beijing","shanghai", "wuhan", "shenzhen", "xian"};

    int count6 = std::count_if(str_vec.begin(), str_vec.end(), longer_than_6);
   
    std::cout << "longer_than_6: " << count6 << std::endl;

    int count3 = std::count_if(str_vec.begin(), str_vec.end(), LongThan(3));
    std::cout << "count3:" << count3 << std::endl;

    return 0;
}
