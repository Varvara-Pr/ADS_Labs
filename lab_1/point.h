#pragma once
#include <iostream>
#include <complex>

template<typename T>
struct Point {
    T _x, _y;
    Point() : _x(T()), _y(T()) {}
    Point(T x, T y) : _x(x), _y(y) {}
    Point(const Point& other) : _x(other._x), _y(other._y) {}

    bool operator==(const Point& p) const {
        return _x == p._x && _y == p._y;
    }

    bool operator!=(const Point& p) const {
        return !(*this == p);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    os << "(" << p._x << ", " << p._y << ")";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Point<std::complex<T>>& p) {
    os << "(" << p._x.real() << "+" << p._x.imag() << "i, "
        << p._y.real() << "+" << p._y.imag() << "i)";
    return os;
}