#pragma once

#include "board.hpp"

// clasa de baza abstracta pentru redare
class Drawable {
public:
    virtual void DrawBoard(const Board& board) = 0;
    virtual ~Drawable() {}
};
