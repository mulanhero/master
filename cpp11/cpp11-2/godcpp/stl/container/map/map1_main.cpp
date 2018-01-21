#include <iostream>
#include <map>

using namespace std;

class Book {
public:
    Book() {
    }

    Book(string &name, string &author) :
            name(name), author(author) {
    }

    ~Book() {
    }

    string& getName() {
        return name;
    }

    string& getAuthor() {
        return author;
    }

    friend ostream& operator<<(ostream &out, Book &b) {
        out << "name:" << b.name << ", author:" << b.author;
        return out;
    }

private:
    string name;
    string author;
};

class Library {
public:
    void add(string &id, string &name, string &author) {
        id2Book[id] = Book(name, author);
    }

    Book& get(string &id) {
        return id2Book[id];
    }

private:
    map<string, Book> id2Book;
};

int main() {
    Library lib;
    string id1("00001");
    string name1("name1");
    string author1("author1");
    lib.add(id1, name1, author1);

    string id2("00002");
    string name2("name2");
    string author2("author2");
    lib.add(id2, name2, author2);

    string key("00001");
    Book& book = lib.get(key);
    cout << book << endl;
    return 0;
}
