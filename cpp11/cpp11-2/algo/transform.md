#transform

##0 prototypes

	template <class InputIterator, class OutputIterator, class UnaryOperation>    
	OutputIterator transform (InputIterator first1, InputIterator last1,
                              OutputIterator result, UnaryOperation op);

	template <class InputIterator1, class InputIterator2,
          class OutputIterator, class BinaryOperation>
   	OutputIterator transform (InputIterator1 first1, InputIterator1 last1,
                            InputIterator2 first2, OutputIterator result,
                            BinaryOperation binary_op);
	

##1 例子

###1.1 eg1
	std::vector<int>  vec1 = {1, 2, 3, 4, 5};
    std::vector<int> vec2;

    vec2.resize(vec1.size());
    //vec1中每个元素乘以10，添加到vec2中
    std::transform(vec1.begin(), vec1.end(), vec2.begin(), [](int i)->int{ return i * 10;});
    std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    //vec1和vec2每个位置上的元素相加，写回到vec1中
    std::transform(vec1.begin(), vec1.end(), vec2.begin(), vec1.begin(), std::plus<int>());
    std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    //vec1中每个元素乘方，然后添加到vec2元素的后面
    std::transform(vec1.begin(), vec1.end(), std::back_inserter(vec2), [](int i)->int {return i * i;});
    std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>(std::cout, " "));

	

----------
	10 20 30 40 50 
	11 22 33 44 55 
	10 20 30 40 50 121 484 1089 1936 3025


###1.2 eg2

如果transform在一个vec上运算，最后写回，其作用和for_each相似
    
	std::vector<int>  vec1 = {1, 2, 3, 4, 5};

    std::transform(vec1.begin(), vec1.end(), vec1.begin(), [](int i)->int {return 2 * i;});
    std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::for_each(vec1.begin(), vec1.end(), [](int& i){ i *= 2;} );
    std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;