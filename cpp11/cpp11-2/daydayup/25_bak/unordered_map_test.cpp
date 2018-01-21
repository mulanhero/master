#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
 
using namespace std;
 
template <class T>
void show(const T& x)
{
    for (const auto& i : x)
        cout << i.first << "; " << i.second << endl;
}
 
template <template <class ...> class T>
void test()
{
    T<string, int> x;
    x.insert(make_pair("one", 1));
    x.insert(make_pair("two", 2));
    x.insert(make_pair("three", 3));
    x.insert(make_pair("four", 4));
    //really cool!
    x.insert({"five", 5});
     
    show(x);
}
 
 
 
int main()
{
  test<map>();
  cout << "*******************" << endl;
  test<unordered_map>();
}
