#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>


std::vector<std::string> return_by_value() {
    std::vector<std::string> tmp = {"shanghai", "beijing", "xian"};
    return tmp;
}
//Notice: when returned by ref, another variable returned_2 only is to get the alias name, then the tmp's memory is deallocated
std::vector<std::string>& return_by_ref() {
    std::vector<std::string> tmp = {"shanghai", "beijing", "xian"};
    return tmp;
}



int main() {
    std::vector<std::string> returned_1 = return_by_value();
    copy(returned_1.begin(), returned_1.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

   //error, ref to rvalue, it will be deallocated soon
   /*
    std::vector<std::string>& returned_11 = return_by_value();
    copy(returned_11.begin(), returned_11.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    */

   /* 
    std::cout << "-----------------" << std::endl;
    std::vector<std::string> returned_2 = return_by_ref();
    copy(returned_2.begin(), returned_2.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    */
    
    return 0;
}
