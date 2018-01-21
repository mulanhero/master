#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
    std::string filename = "tmp.txt";
    
    std::ofstream file1(filename.c_str());
    for (int i = 33; i < 88; ++i) {
        file1 << "index:" << i << ", char:" << std::setw(8) << static_cast<char>(i) << std::endl;
    }
    file1.flush();
    file1.close();

    std::ifstream file2(filename.c_str());
    //std::cout << file2.rdbuf();
    char ch;
    while (file2.get(ch)) {
        std::cout.put(ch);
    }

    std::remove(filename.c_str());
    std::remove("a.out");
    
    return 0;
}
