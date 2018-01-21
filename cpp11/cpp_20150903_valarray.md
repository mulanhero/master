#valarray
##1 简介
`#include<valarray>` vector是一维数组，而valarray是向量，可以对其做整体运算。

##2 格式
###2.1 构造函数

	valarray<T> va;
	valarray<T> va = {...}; //初始化列表
	valarray<T> va(n);
	valarray<T> va(val, n);
	valarray<T> va(array, n);
	valarray<T> va(va2);
 
###2.2 成员函数
	
	resize(n);
	size(n);
	operator[]
	operator+(-*/~)

##3 示例
###3.1 eg-1
	std::valarray<float> va = {1.1, 1.1, 1.1}; //初始化列表
    va *= 2;
    for (size_t i = 0; i < va.size(); ++i) {
        std::cout << va[i] << std::endl;
    }
	
###3.2 eg-2
	
	std::valarray<float> va1(1.1, 4); 
    va1 *= 2;
    va1 = -va1;
    for (int i = 0; i < va1.size(); ++i) {
        std::cout << va1[i] << std::endl;
    }

###3.3 eg-3

	float array[] = {2.2, 2.2, 2.2, 2.2};
    std::valarray<float> va1(1.1, 4); 
    std::valarray<float> va2(array, 4); 
    va1 *= va2;    //向量乘
    for (auto& it : va1)  {
        std::cout << it << std::endl;
    }