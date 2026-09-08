#include "listener.hpp"
#include <iostream>

Point Listener::GetMove() {
    Point move;
    std::cout << "Introduceti randul si coloana (0-2): ";
    std::cin >> move.row >> move.col;
    return move;
}

bool Listener::WantsToQuit() {
    return false;
}