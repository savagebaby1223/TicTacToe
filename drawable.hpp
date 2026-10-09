#pragma once

#include "board.hpp"

// clasa de baza abstracta pentru redare
class Drawable {
public:
    // metoda virtuala pura - orice clasa de redare trebuie sa o implementeze
    virtual void DrawBoard(const Board& board) = 0;

    // destructor virtual (bun stil la clase de baza)
    virtual ~Drawable() {}
};