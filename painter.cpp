#include "painter.hpp"
#include <iostream>

void Painter::DrawBoard(const Board& board) const {
    std::cout << board;   // foloseste operator<< definit pe Board
}

void Painter::WriteMessage(const std::string& text) const {
    std::cout << text << '\n';
}

void Painter::ClearScreen() const {
    // afiseaza linii goale pentru a "curata" ecranul consolei
    for (int i = 0; i < 20; i++) std::cout << '\n';
}
