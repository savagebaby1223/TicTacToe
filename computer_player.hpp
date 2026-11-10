#pragma once

#include "player.hpp"

// jucator controlat de calculator, foloseste algoritmul minimax:
// analizeaza toate mutarile posibile pana la finalul jocului si alege cea mai buna,
// deci nu pierde niciodata (castiga sau face remiza)
class ComputerPlayer : public Player {
    // scorul unei pozitii: pozitiv daca calculatorul castiga, negativ daca pierde, 0 la remiza
    int Minimax(const Board& board, bool myTurn, int depth) const;
public:
    ComputerPlayer(Cell symbol);

    Point GetMove(const Board& board) const override;
};
