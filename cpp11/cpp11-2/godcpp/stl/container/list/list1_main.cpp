#include <list>
#include <iostream>
using namespace std;

class Item {
public:
    Item(string &name, double price) :
            name(name), price(price) {
    }
    ~Item() {
    }

    string &getName() {
        return this->name;
    }

    double getPrice() {
        return this->price;
    }
private:
    string &name;
    double price;
};

int main() {
    list<Item> itemList;
    string str1("str1");
    Item item1(str1, 1.1);
    itemList.push_back(item1);

    string str2("str2");
    Item item2(str2, 2.2);
    itemList.push_front(item2);

    cout << "count:" << itemList.size() << endl;

    list<Item>::iterator i;
    for (i = itemList.begin(); i != itemList.end(); i++) {
        cout << "name:" << i->getName() << ", price:" << i->getPrice() << endl;
    }

    //erase the element from head
    list<Item>::iterator it = itemList.erase(itemList.begin());
    cout << "after removed, (it) points to the header, see: name: " << (*it).getName() << ", price:"
            << (*it).getPrice() << endl;

    cout << "after remove, cout:" << itemList.size() << endl;
    for (list<Item>::iterator it = itemList.begin(); it != itemList.end(); it++) {
        cout << "name:" << it->getName() << ", price:" << it->getPrice() << endl;
    }

    return 0;
}
