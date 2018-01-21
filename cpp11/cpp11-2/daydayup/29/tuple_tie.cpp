#include <tuple>
#include <iostream>
#include <functional>


void test1() {
    //1. std::tuple<std::string, int>
    //2. std::make_tuple
    //3. std::get<0>(obj)
    std::tuple<std::string, int> person = std::make_tuple("jimmy", 34);
    std::cout << std::get<0>(person) << std::endl; 
    std::cout << std::get<1>(person) << std::endl; 
}

void test2() {
    //1. auto
    //2. std::ref
    int age = 34;
    auto person = std::make_tuple("jimmy", std::ref(age));
    std::cout << std::get<0>(person) << std::endl; 
    std::cout << std::get<1>(person) << std::endl; 

    age = 35;
    std::cout << std::get<1>(person) << std::endl; 
}


void test3() {
    //1. std::tie
    std::string name;
    int age;
    auto person = std::make_tuple("jimmy", 34);
    std::tie(name, age) = person; //unpack data into variable, tie will keep the image of current tuple
    std::cout << name << std::endl;
    std::cout << age << std::endl;
    std::get<1>(person) = 36;
    std::cout << age << std::endl;
    std::cout << std::get<1>(person) << std::endl;
}

void test4() {
    //std::tuple_cat
    std::tuple<std::string, int> person_basic("jimmy", 34);
    std::pair<std::string, std::string> person_id_phone("61032419", "18817879959");
    auto person = std::tuple_cat(person_basic, person_id_phone);
    std::cout << std::get<0>(person) << std::endl;
    std::cout << std::get<1>(person) << std::endl;
    std::cout << std::get<2>(person) << std::endl;
    std::cout << std::get<3>(person) << std::endl;
}
int main() {

    std::cout << "--------------1" << std::endl;
    test1();
    std::cout << "--------------2" << std::endl;
    test2();
    std::cout << "--------------3" << std::endl;
    test3();
    std::cout << "--------------4" << std::endl;
    test4();
    return 0;
}
