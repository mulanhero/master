#list

##背景
list是一个双向链表

##成员函数

###erase()
###pop_front()
###pop_back()
###front()
###back()

##举例
###eg1
	std::list<int> mylist = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    //erase一个
    auto it = std::find(mylist.begin(), mylist.end(), 4);
    if (it != mylist.end()) {
        mylist.erase(it);
    }
    std::copy(mylist.begin(), mylist.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

	//erase一批
    mylist.erase(std::remove(mylist.begin(), mylist.end(), 2), mylist.end());
    std::copy(mylist.begin(), mylist.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
	
	//front() back()
    std::cout << "front is:" << mylist.front() << ", back is:" << mylist.back() << std::endl;
	//pop_front()
    mylist.pop_front();
    std::copy(mylist.begin(), mylist.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
	//pop_back()
    mylist.pop_back();
    std::copy(mylist.begin(), mylist.end(), std::ostream_iterator<int>(std::cout, " "));