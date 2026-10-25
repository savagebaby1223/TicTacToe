#include "painter.hpp"
#include <iostream>

void Painter::DrawBoard(const Board& board) {
    std::cout << board;   // foloseste operator<< definit pe Board
}

void Painter::WriteMessage(const std::string& text) {
    std::cout << text << '\n';
}

void Painter::ClearScreen() {
    // afiseaza linii goale pentru a "curata" ecranul consolei
    for (int i = 0; i < 20; i++) std::cout << '\n';
}
