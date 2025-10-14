#include <iostream>
#include "polyline.h"
#include "functions.h"

using namespace std;

int main() {
    cout << "Lab 1: Variant 5 Task 2\nProskurnina Varvara 6212\n\n";

    cout << "1. Random polyline with range [10, 50]: ";
    Polyline<int> randomLine(4, 10, 50);
    cout << randomLine << "\n";
    cout << "Size: " << randomLine.size() << "\n\n";

    cout << "2. Operator []:\n";
    cout << "First point: " << randomLine[0] << "\n";
    randomLine[1] = Point<int>(99, 99);
    cout << "Rewrote the second point: " << randomLine << "\n\n";

    cout << "3. Addition operators:\n";
    cout << "Point + Polyline: " << (Point<int>(-1, -1) + randomLine) << "\n";
    cout << "Polyline + Point: " << (randomLine + Point<int>(100, 100)) << "\n";

    Polyline<int> otherLine(2, 60, 80);
    cout << "Another polyline: " << otherLine << "\n";
    cout << "Polyline + Polyline: " << (randomLine + otherLine) << "\n\n";

    cout << "4. Different types:\n";
    cout << "double [0.5, 5.5]: " << Polyline<double>(3, 0.5, 5.5) << "\n";
    cout << "float [1.0, 3.0]: " << Polyline<float>(2, 1.0f, 3.0f) << "\n\n";

    return 0;
}