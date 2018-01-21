#include <iostream>
#include <vector>

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
        return price;
    }
private:
    string &name;
    double price;
};

int main() {
    vector<Item> v;
    string str1("str1");
    Item item1(str1, 1.1);
    v.push_back(item1);

    string str2("str2");
    Item item2(str2, 1.1);
    v.push_back(item2);

    cout << "v.size():" << v.size() << endl;

    vector<Item>::iterator i;
    for (i = v.begin(); i != v.end(); ++i) {
        cout << "name:" << i->getName() << ", price:" << i->getPrice() << endl;
    }
    return 0;
}
