#pragma once

#include <iostream>
#include "cell.hpp"
#include "point.hpp"

class Board;  // forward declaration

// clasa de baza abstracta pentru orice jucator
class Player {
protected:
    Cell _symbol;
public:
    Player(Cell symbol);
    virtual ~Player() {}

    Cell GetSymbol() const;

    // metoda virtuala pura: fiecare tip de jucator alege mutarea in felul lui
    virtual Point GetMove(const Board& board) const = 0;
};
