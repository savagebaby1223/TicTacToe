#pragma once

#include "board.hpp"

// clasa de baza abstracta pentru redare
class Drawable {
public:
    // const: desenarea doar citeste tabla, nu modifica nimic
    virtual void DrawBoard(const Board& board) const = 0;
    virtual ~Drawable() {}
};
