#pragma once

#include <iostream>

struct Point {
    int row;
    int col;

    Point();
    Point(int row, int col);

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
};

std::ostream& operator<<(std::ostream& out, const Point& p);
std::istream& operator>>(std::istream& in, Point& p);
