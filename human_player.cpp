#include "human_player.hpp"
#include "board.hpp"
#include <iostream>

HumanPlayer::HumanPlayer(Cell symbol) : Player(symbol) {}

Point HumanPlayer::GetMove(const Board& board) const {
    Point move;
    std::cout << "Introduceti randul si coloana (0-2): ";
    std::cin >> move;   // foloseste operator>> definit pe Point
    return move;
}
