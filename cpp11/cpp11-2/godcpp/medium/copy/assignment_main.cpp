#include <iostream>
#include <iostream>

using namespace std;

class Book {
public:
    Book(string &name, double price);
    virtual ~Book() {
    }

    Book(const Book &book);

    Book& operator=(const Book &book);

    friend ostream& operator<<(ostream &out, Book &book);

private:
    string name;
    double price;
};

Book::Book(string &name, double price) {
    this->name = name;
    this->price = price;
}

/*
 There are three general cases where the copy constructor is called instead of the assignment operator:
 When instantiating one object and initializing it with values from another object.
 When passing an object by value.
 When an object is returned from a function by value.
 */
Book& Book::operator=(const Book &book) {
    this->name = book.name;
    this->price = book.price;
    return *this;
}

ostream& operator<<(ostream &out, Book &book) {
    out << "name:" << book.name << ", price:" << book.price;
    return out;
}

int main() {
    string name1("BookName1");
    Book b1(name1, 10);
    cout << b1 << endl;
    return 0;
}
