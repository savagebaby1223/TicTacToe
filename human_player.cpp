#include "human_player.hpp"
#include "board.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>

HumanPlayer::HumanPlayer(Cell symbol) : Player(symbol) {}

Point HumanPlayer::GetMove(const Board& board) const {
    Point move;
    std::cout << "Jucatorul " << (_symbol == Cell::X ? 'X' : 'O')
              << ", introduceti randul si coloana (0-2): ";
    // daca nu se introduc numere, curat fluxul si cer din nou
    while (!(std::cin >> move)) {
        if (std::cin.eof()) std::exit(0);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Introduceti doua numere (0-2): ";
    }
    return move;
}
