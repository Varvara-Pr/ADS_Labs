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
        _vertices = new Point<T>[_capacity];
        _vertices[0] = point;
    }

    Polyline(size_t count) {
        _vertices = new Point<T>[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            _vertices[i] = Point<T>();
        }
    }

    Polyline(size_t count, T m_1, T m_2) : _size(count), _capacity(count) {
        if (count == 0) {
            _vertices = nullptr;
            return;
        }
        _vertices = new Point<T>[_capacity];
        std::random_device rd;
        std::mt19937 gen(rd());

        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(m_1, m_2);
            for (size_t i = 0; i < count; ++i) {
                _vertices[i] = Point<T>(dist(gen), dist(gen));
            }
        }
        else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dist(m_1, m_2);
            for (size_t i = 0; i < count; ++i) {
                _vertices[i] = Point<T>(dist(gen), dist(gen));
            }
        }
        else {
            using ValueType = typename T::value_type;
            if constexpr (std::is_same_v<T, std::complex<ValueType>>) {
                std::uniform_real_distribution<ValueType> dist_real(m_1.real(), m_2.real());
                std::uniform_real_distribution<ValueType> dist_imag(m_1.imag(), m_2.imag());
                for (size_t i = 0; i < count; ++i) {
                    _vertices[i] = Point<T>(
                        T(dist_real(gen), dist_imag(gen)),
                        T(dist_real(gen), dist_imag(gen))
                    );
                }
            }
            else {
                for (size_t i = 0; i < count; ++i) {
                    _vertices[i] = Point<T>(m_1, m_2);
                }
            }
        }
    }


    Polyline(const Polyline& other) : _size(other._size), _capacity(other._size) {
        if (other._size > 0) {
            _vertices = new Point<T>[other._size];
            for (size_t i = 0; i < other._size; ++i) {
                _vertices[i] = other._vertices[i];
            }
        }
        else {
            _vertices = nullptr;
        }
    }

    ~Polyline() {
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
            Point<T>* new_vertices = new Point<T>[new_capacity];

            for (size_t i = 0; i < _size && i < new_capacity; ++i) {
                new_vertices[i] = _vertices[i];
            }

            delete[] _vertices;
            _vertices = new_vertices;
            _capacity = new_capacity;
        }

        if (_size < _capacity) {
            _vertices[_size] = point;
            _size++;
        }
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

    Polyline& operator=(const Polyline& other) {
        if (this != &other) {
            delete[] _vertices;

            _size = other._size;
            _capacity = other._capacity;

            if (other._vertices) {
                _vertices = new Point<T>[other._capacity];
                for (size_t i = 0; i < other._size; ++i) {
                    _vertices[i] = other._vertices[i];
                }
            }
            else {
                _vertices = nullptr;
            }
        }
        return *this;
    }

    /*bool operator==(const Polyline<T>& other) const {
    }

    bool operator!=(const Polyline<T>& other) const {
    }*/

    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }

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
