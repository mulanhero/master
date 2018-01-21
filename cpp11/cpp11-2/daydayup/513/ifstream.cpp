#include <iostream>
#include <fstream>

int main() {
    std::string line;

    //std::string filename = "/etc/ok";
    std::string filename = "/etc/passwd";
    std::ifstream infile(filename);

    if (!infile) {
        std::cerr << "failed to open file:" << filename << std::endl;
        return -1;
    }

    if (!getline(infile, line).good()) {
        std::cerr << "getline from file failed:" << std::endl;
        return -1;
    }

    while(std::getline(infile, line)) {
        std::cout << line << std::endl;
    }
    return 0;
}
