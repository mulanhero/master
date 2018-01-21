#include <iostream>

template <class T>
class Poly {
public:
    Poly(T length, T width) : _length(length), _width(width) {}

    T get_area() const;
private:
    T _length;
    T _width;
};


template <class T>
T Poly<T>::get_area() const {
    return _length * _width;
}

int main () {
    Poly<int> pi(3, 4);
    std::cout << pi.get_area() << std::endl;

    Poly<double> pd(3.3, 4.4);
    std::cout << pd.get_area() << std::endl;
    return 0;
}
