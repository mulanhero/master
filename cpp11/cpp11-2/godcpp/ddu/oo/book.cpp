#include <iostream>
#include <string>

class Book {
public:
    Book(std::string& isbn="", double price=0.0) :
        _isbn(isbn), _price(price) {}

    virtual ~Book() = default;

    std::string get_isbn() const {
        return _isbn;
    }

    virtual double total_price(std::size_t num) const {
        return num * price;
    }
protected:
    std::string _isbn;
private:
    double _price;
};


class ChildBook : Book {


};
