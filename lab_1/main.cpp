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

    cout << "4. Comparison operators:\n";
    Polyline<int> copyLine = randomLine;
    cout << "randomLine == copyLine: " << (randomLine == copyLine) << "\n";
    cout << "randomLine != copyLine: " << (randomLine != copyLine) << "\n";

    Polyline<int> differentLine(2, 1, 5);
    cout << "randomLine == differentLine: " << (randomLine == differentLine) << "\n";
    cout << "randomLine != differentLine: " << (randomLine != differentLine) << "\n\n";

    cout << "5. Different types:\n";
    cout << "double [0.5, 5.5]: " << Polyline<double>(3, 0.5, 5.5) << "\n";
    cout << "float [1.0, 3.0]: " << Polyline<float>(2, 1.0f, 3.0f) << "\n\n";

    Polyline<double> doubleLine(3, 0.5, 5.5);
    cout << "double [0.5, 5.5]: " << doubleLine << "\n";
    cout << "Length (double): " << doubleLine.length() << "\n";

    Polyline<float> floatLine(2, 1.0f, 3.0f);
    cout << "float [1.0, 3.0]: " << floatLine << "\n";
    cout << "Length (float): " << floatLine.length() << "\n";

    using Complex = std::complex<double>;
    Polyline<Complex> complexLine(2, Complex(1.0, 1.0), Complex(3.0, 3.0));
    cout << "complex [1+1i, 3+3i]: " << complexLine << "\n";
    cout << "Length (complex): " << complexLine.length() << "\n\n";


    return 0;
}