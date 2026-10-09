#pragma once

#include <iostream>

struct Point {
	int row;
	int col;

	// constructor implicit
	Point();
	// constructor cu parametri
	Point(int row, int col);
	// constructor de copiere
	Point(const Point& other);
	// operator de atribuire
	Point& operator=(const Point& other);
	// operatori de comparare
	bool operator==(const Point& other) const;
	bool operator!=(const Point& other) const;
};

// operatori de intrare / iesire (functii libere, nu metode)
std::ostream& operator<<(std::ostream& out, const Point& p);
std::istream& operator>>(std::istream& in, Point& p);