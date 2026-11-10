#pragma once

#include <array>
#include <iostream>
#include "cell.hpp"
#include "point.hpp"

class Board {
    // container STL in loc de C-array
    std::array<std::array<Cell, 3>, 3> _cells;
public:
    Board();

    void Reset();
    bool PlaceSymbol(const Point& position, Cell symbol);
    Cell GetCell(const Point& position) const;
    bool IsFull() const;
    bool IsValid(const Point& position) const;
    // simbolul care are 3 in linie (X sau O), sau Empty daca nu a castigat nimeni
    Cell GetWinner() const;
};

std::ostream& operator<<(std::ostream& out, const Board& b);
