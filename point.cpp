#include "point.hpp"

Point::Point() {
    row = 0;
    col = 0;
}

Point::Point(int row, int col) {
    this->row = row;
    this->col = col;
}

Point::Point(const Point& other) {
    row = other.row;
    col = other.col;
}

Point& Point::operator=(const Point& other) {
    row = other.row;
    col = other.col;
    return *this;
}

bool Point::operator==(const Point& other) const {
    return row == other.row && col == other.col;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << "(" << p.row << ", " << p.col << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Point& p) {
    in >> p.row >> p.col;
    return in;
}