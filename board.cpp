#include "board.hpp"

Board::Board() {
    Reset();
}

void Board::Reset() {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            _cells[r][c] = Cell::Empty;
        }
    }
}

bool Board::PlaceSymbol(const Point& position, Cell symbol) {
    if (_cells[position.row][position.col] != Cell::Empty) {
        return false;
    }
    _cells[position.row][position.col] = symbol;
    return true;
}

Cell Board::GetCell(const Point& position) const {
    return _cells[position.row][position.col];
}

bool Board::IsFull() const {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (_cells[r][c] == Cell::Empty) {
                return false;
            }
        }
    }
    return true;
}