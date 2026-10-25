#pragma once

#include "player.hpp"

class HumanPlayer : public Player {
public:
    HumanPlayer(Cell symbol);

    // citeste mutarea de la tastatura
    Point GetMove(const Board& board) const override;
};
