#include "computer_player.hpp"
#include "board.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

ComputerPlayer::ComputerPlayer(Cell symbol) : Player(symbol) {}

// cauta o mutare care aliniaza 3 simboluri pentru 'symbol'
Point ComputerPlayer::FindWinningMove(const Board& board, Cell symbol) const {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            Point p{ r, c };
            if (board.GetCell(p) != Cell::Empty) continue;
            // simuleaza mutarea pe o copie a tablei
            Board copy = board;
            copy.PlaceSymbol(p, symbol);
            // verifica daca acum exista o linie de 3 'symbol'
            for (int i = 0; i < 3; i++) {
                if (copy.GetCell({ i,0 }) == symbol && copy.GetCell({ i,1 }) == symbol && copy.GetCell({ i,2 }) == symbol) return p;
                if (copy.GetCell({ 0,i }) == symbol && copy.GetCell({ 1,i }) == symbol && copy.GetCell({ 2,i }) == symbol) return p;
            }
            if (copy.GetCell({ 0,0 }) == symbol && copy.GetCell({ 1,1 }) == symbol && copy.GetCell({ 2,2 }) == symbol) return p;
            if (copy.GetCell({ 0,2 }) == symbol && copy.GetCell({ 1,1 }) == symbol && copy.GetCell({ 2,0 }) == symbol) return p;
        }
    }
    return { -1, -1 };  // nu exista mutare castigatoare
}

Point ComputerPlayer::GetMove(const Board& board) const {
    std::cout << "Calculatorul alege mutarea...\n";

    // simbolul adversarului
    Cell opponent = (_symbol == Cell::X) ? Cell::O : Cell::X;

    // 1. daca poate castiga, castiga
    Point win = FindWinningMove(board, _symbol);
    if (win != Point{ -1, -1 }) return win;

    // 2. daca adversarul poate castiga la urmatoarea, blocheaza
    Point block = FindWinningMove(board, opponent);
    if (block != Point{ -1, -1 }) return block;

    // 3. altfel: colecteaza toate casutele libere si ia prima (algoritm STL)
    std::vector<Point> free;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board.GetCell({ r, c }) == Cell::Empty)
                free.push_back({ r, c });

    if (!free.empty()) return free.front();
    return { -1, -1 };
}
