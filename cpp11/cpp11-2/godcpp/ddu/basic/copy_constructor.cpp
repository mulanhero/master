/*
 * copy_constructor.cpp
 *
 *  Created on: 2015年2月28日
 *      Author: caohaijun
 */
#include <iostream>

class Point {
public:
    Point(): _x(0), _y(0) {
    }

    Point(int x, int y): _x(x), _y(y) {
    }

    ~Point() = default;

    Point(const Point& p) {
        std::cout << "copy construct is called" << std::endl;
        copy(p);
    }

    Point& operator=(const Point& p) {
        std::cout << "operator =  is called" << std::endl;
        if (&p ==this) {
            return *this;
        }
        copy(p);
        return *this;
    }

    void print() {
        std::cout << "_x: " << _x << ", _y:" << _y << std::endl;
    }

    void set_x(int x) {
        _x = x;
    }

    void set_y(int y) {
        _y = y;
    }

    int get_x() {
        return _x;
    }

    int get_y() {
        return _y;
    }



private:
    void copy(const Point& p) {
        _x = p._x;
        _y = p._y;
    }

    int _x;
    int _y;
};

void func_by_value(Point p) {
    std::cout << "in func_by_value()" << std::endl;
}

void func_by_ref(Point& p) {
    std::cout << "in func_by_ref" << std::endl;
}

Point return_by_value(Point& p) {
    return p;
}

Point& return_by_ref(Point& p) {
    return p;
}



int main() {
    Point p1(1,1);
    func_by_value(p1);
    Point p2_value = p1;
    std::cout << "--------1-------"  << std::endl;

    func_by_ref(p1);
    Point& p2_ref = p1;

    std::cout << "------2---------"  << std::endl;
    Point p3;
    p3 = p1; //operaotr=

    std::cout << "--------3-------"  << std::endl;
    Point p4 = return_by_value(p1);
//    Point& p5 = return_by_value(p1);  //failuer, can not give a alias
    const Point& p5 = return_by_value(p1);//success, equals
//    Point p9;
//    p9 = return_by_value(p1);

    std::cout << "---------4------"  << std::endl;
    Point& P6 = return_by_ref(p1);
    Point p7 = return_by_ref(p1);
    Point p8;
    p8 = return_by_ref(p1);

    return 0;
}


