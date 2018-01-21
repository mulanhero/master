#include <iostream>
#include <memory>
#include <vector>

template<class T, class... ARGS>
std::unique_ptr<T> make_unique(ARGS && ... args) {
    return std::unique_ptr<T>(new T(std::forward<ARGS>(args)...));
}

int main() {
    std::vector<std::unique_ptr<std::string>> cities;
    std::unique_ptr<std::string> beijing_ptr = make_unique<std::string>(std::move("beijing"));
    std::unique_ptr<std::string> shanghai_ptr = make_unique<std::string>(std::move("shanghai"));
    cities.push_back(std::move(beijing_ptr));
    cities.push_back(std::move(shanghai_ptr));

    for (auto&  city : cities) {
        std::cout << *city << std::endl;
    }

    return 0;
}
