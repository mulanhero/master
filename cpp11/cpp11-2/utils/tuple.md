# tuple #
##0 简介 ##
**tuple** 是一种特殊的容器，与**pair** 相比，**tuple**可以容纳更多的元素。

要使用tuple，必须`#include <tuple>`.

##1 申明同时初始化，用make_tuple()构建，get<>()成员##
可以先申明，然后通过**make_tuple** 初始化，然后通过**get<>()** 来获取元素值。 

	#include <tuple>
    std::tuple<std::string, int, bool> p1("somebody", 0, false);
	std::cout << std::get<0>(p1) << std::endl;

    p1 = std::make_tuple("jimmy", 31, false);
    std::cout << std::get<0>(p1) << std::endl;

	auto p2 = std::make_tuple("amao", 34, true);
	std::cout << std::get<1>(p2) << std::endl;

##2 tuple中存放引用std::ref()##
tuple中可以存放变量的引用**std::ref()** 或者常引用**std::cref()**。 若是std::ref(),则

注意：ref()和cref()在头文件`#include <functional>` 中

    #include <functional>
	int age = 35;
 	std::string gender = "male";
	auto p1 = std::make_tuple("amao", std::ref(age), std::cref(gender));
	std::get<1>(p1) = 36;
	std::cout <<　age << std::endl;  //will output 36

##3 用std::tie把tuple中元素值unpack到变量中保存现场 ##
保存现场后，修改tuple中元素的值将不影响保存现场中的值。
	
	std::string name;
	int age;
	std::string gender;
	
	auto person = std::make_tuple("amao", 35, "male");	
	std::tie(name, age, gender) = person;

	std::get<1>(person) = 36;
	std::cout <<　age << std::endl; // will output 35 (not changed)

##4 用std::tuple_cat连接两个tuple ##
把两个tuple连接起来，生成一个新的tuple。

	std::tuple<std::string, int, bool> p1("somebody", 0, false);
	
	std::string phone = "188888888888";
	unsigned long postcode = "100085";
	auto p2 = std::make_tuple(phone, postcode);
	
	auto full = std::tuple_cat(p1, p2);
	std::cout <<　std::get<3>(full) << std::endl;