#include <iostream>
using namespace std;

class Date {
public:
    Date(int day, int month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    int getDay() const {
        return this->day;
    }

    int getMonth() const {
        return this->month;
    }

    int getYear() const {
        return this->year;
    }
private:
    int day;
    int month;
    int year;
};

void printDate(const Date & date) {
    cout << "Year: " << date.getYear() << ", Month:" << date.getMonth()
            << ", Day:" << date.getDay() << endl;
}

int main() {
    const Date date(1, 1, 2014);
    printDate(date);
    return 0;
}
