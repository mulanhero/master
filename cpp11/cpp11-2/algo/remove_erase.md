#remove erase
#背景
remove不会真的把元素删除，只是把未删除的元素向前copy覆盖已经删除的元素位置，不会调用resize()。

#举例

##eg1

	#include <iostream>
	#include <vector>
	#include <algorithm>
	#include <iterator>
	
	int main() {
	    std::vector<int> vec = {1, 2, 3, 1, 2, 3, 1, 2, 3};
		//抹除值为3的元素，把后面的元素copy覆盖被删除的元素位置，其返回新的'end'
	    auto end = std::remove(vec.begin(), vec.end(), 3);
		//size()不变
	    std::cout << vec.size() << std::endl;
		
		//真正删除要靠erase(),其会调用resize()
	    vec.erase(end, vec.end());
	    std::cout << vec.size() << std::endl;
	    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	
	}

	9
	6
	1 2 1 2 1 2


##eg2 list 
erase删除一个值确定的元素，remove_erase所有值确定的元素

	#include <iostream>
	#include <list>
	#include <algorithm>
	#include <iterator>
	
	int main() {
	    std::list<int> mylist = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
	
	    //erase一个元素
	    auto it = std::find(mylist.begin(), mylist.end(), 4);
	    if (it != mylist.end()) {
	        mylist.erase(it);
	    }
	    std::copy(mylist.begin(), mylist.end(), std::ostream_iterator<int>(std::cout, " "));
	    std::cout << std::endl;

		//先remove，后erase所有值为2的元素
	    mylist.erase(std::remove(mylist.begin(), mylist.end(), 2), mylist.end());
	    std::copy(mylist.begin(), mylist.end(), std::ostream_iterator<int>(std::cout, " "));
	}