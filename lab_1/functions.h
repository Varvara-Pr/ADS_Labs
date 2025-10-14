#pragma once
#include "polyline.h"
#include <stdexcept>

template<typename T>
Polyline<T> createRectangularTrapezoid(T a, T b, T h) {
    if (a <= 0 || b <= 0 || h <= 0) {
        throw std::invalid_argument("Parameters must be positive");
    }

    Polyline<T> trapezoid;
    trapezoid.push_back(Point<T>(T(0), T(0)));
    trapezoid.push_back(Point<T>(a, T(0)));  
    trapezoid.push_back(Point<T>(b, h));
    trapezoid.push_back(Point<T>(T(0), h));
    trapezoid.push_back(Point<T>(T(0), T(0)));

    return trapezoid;
}