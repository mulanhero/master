#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iomanip>

int main() {
    std::string filename = "tmp.txt";
    std::ofstream file(filename.c_str());
    if(!file) {
        std::cerr << "open file " << filename << " failed" << std::endl;
        exit(-1);
    }
    for (int i = 33; i < 88; ++i) {
        file << "index:" << i << ", char:" << std::setw(4) << static_cast<char>(i) << std::endl;
    }

    file.flush();
    file.close();

    std::ifstream file2(filename);
    //std::cout << file2.rdbuf();
    char ch;
    while (file2.get(ch)) {
        std::cout.put(ch);
    }
    std::remove(filename.c_str());
    std::remove("a.out");
    return 0;
}
