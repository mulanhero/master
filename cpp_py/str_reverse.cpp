#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    typedef std::string::size_type SIZE_T;
    std::string line;
    std::string delims = " \t.;,\n";

    while (getline(std::cin, line)) {
        SIZE_T start = line.find_first_not_of(delims); 
        while (start != std::string::npos) {
            SIZE_T end = line.find_first_of(delims, start);
            std::string word = line.substr(start, end-start);
            reverse(word.begin(), word.end());
            std::cout << word << std::endl;
            start = line.find_first_not_of(delims, end);
        }
        
    }
    return 0;
}
