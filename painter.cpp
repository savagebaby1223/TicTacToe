#include "painter.hpp"
#include <iostream>

void Painter::DrawBoard(const Board& board) {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            Cell cell = board.GetCell({ r, c });
            if (cell == Cell::X) {
                std::cout << " X ";
            }
            else if (cell == Cell::O) {
                std::cout << " O ";
            }
            else {
                std::cout << " . ";
            }
            if (c < 2) {
                std::cout << "|";
            }
        }
        std::cout << std::endl;
    }
}

void Painter::WriteMessage(const Point& position, const char* text) {
    std::cout << text << std::endl;
}

void Painter::ClearScreen() {
    for (int i = 0; i < 30; i++) {
        std::cout << std::endl;
    }
}