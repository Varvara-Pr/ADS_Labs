#pragma once
#include <iostream>
#include <complex>
#include <stdexcept>
#include <random>
#include <cmath>
#include "point.h"


template<typename T>
class Polyline {
private:
    Point<T>* _vertices;
    size_t _size;
    size_t _capacity;
    inline static const double _epsilon = 0.001;

public:
    Polyline() : _vertices(nullptr), _size(0), _capacity(0) {}
    Polyline(const Point<T>& point) : _size(1), _capacity(1) {
        _vertices = new Point<T>[1];
        _vertices[0] = point;
    }

    Polyline(size_t count) {
        _vertices = new Point<T>[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            _vertices[i] = Point<T>();
        }
    }

    /*Polyline(size_t count, T m_1, T m_2) {
    }*/
    /*Polyline(const Polyline& other) {
    }*/
    ~Polyline(){
        delete[] _vertices;
    }

    Point<T>& operator[](size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _vertices[index];
    }

    const Point<T>& operator[](size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _vertices[index];
    }

    void push_back(const Point<T>& point) {
        if (_size >= _capacity) {
            size_t new_capacity = _capacity == 0 ? 1 : _capacity * 2;
            Point<T>* new_points = new Point<T>[new_capacity];

            for (size_t i = 0; i < _size; ++i) {
                new_points[i] = _vertices[i];
            }

            delete[] _vertices;
            _vertices = new_points;
            _capacity = new_capacity;
        }
        _vertices[_size] = point;
        _size++;
    }

    void append(const Polyline& other) {
        for (size_t i = 0; i < other._size; ++i) {
            push_back(other._vertices[i]);
        }
    }

    Polyline operator+(const Polyline& other) const {
        Polyline result = *this;
        result.append(other);
        return result;
    }

    friend Polyline operator+(const Polyline& pl, const Point<T>& point) {
        Polyline result = pl;
        result.push_back(point);
        return result;
    }

    friend Polyline operator+(const Point<T>& point, const Polyline& pl) {
        Polyline result;
        result.push_back(point);
        result.append(pl);
        return result;
    }

    /*double length() const {}
    */

    /*Polyline& operator=(const Polyline& other) {
    }

    bool operator==(const Polyline<T>& other) const {
    }

    bool operator!=(const Polyline<T>& other) const {
    }
    size_t size() const { return _size; }*/

    friend std::ostream& operator<<(std::ostream& os, const Polyline& pl) {
        os << "[";
        for (size_t i = 0; i < pl._size; ++i) {
            os << pl._vertices[i];
            if (i < pl._size - 1) os << ", ";
        }
        os << "]";
        return os;
    }
};
