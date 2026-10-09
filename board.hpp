#pragma once

#include <iostream>
#include "cell.hpp"
#include "point.hpp"

class Board {
	Cell _cells[3][3];
public:
	// constructor implicit
	Board();
	// constructor de copiere
	Board(const Board& other);
	// operator de atribuire
	Board& operator=(const Board& other);
	// operatori de comparare
	bool operator==(const Board& other) const;
	bool operator!=(const Board& other) const;

	void Reset();
	bool PlaceSymbol(const Point& position, Cell symbol);
	Cell GetCell(const Point& position) const;
	bool IsFull() const;
};

std::ostream& operator<<(std::ostream& out, const Board& b);
std::istream& operator>>(std::istream& in, Board& b);