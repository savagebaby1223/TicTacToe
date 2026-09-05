#pragma once

#include "cell.hpp"
#include "point.hpp"

class Board {
	Cell _cells[3][3];
public:
	Board();
	void Reset();
	bool PlaceSymbol(const Point& position, Cell symbol);
	Cell GetCell(const Point& position) const;
	bool IsFull() const;
};