#pragma once

#include "player.hpp"

class ComputerPlayer : public Player {
    // incearca sa gaseasca o mutare castigatoare pentru simbolul dat
    Point FindWinningMove(const Board& board, Cell symbol) const;
public:
    ComputerPlayer(Cell symbol);

    // alege mutarea singur: castiga daca poate, altfel blocheaza, altfel ia prima libera
    Point GetMove(const Board& board) const override;
};
