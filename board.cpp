#include "board.hpp"

Board::Board() {
    Reset();
}

Board::Board(const Board& other) {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            _cells[r][c] = other._cells[r][c];
}

Board& Board::operator=(const Board& other) {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            _cells[r][c] = other._cells[r][c];
    return *this;
}

bool Board::operator==(const Board& other) const {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (_cells[r][c] != other._cells[r][c])
                return false;
    return true;
}

bool Board::operator!=(const Board& other) const {
    return !(*this == other);
}

void Board::Reset() {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            _cells[r][c] = Cell::Empty;
}

bool Board::PlaceSymbol(const Point& position, Cell symbol) {
    if (_cells[position.row][position.col] != Cell::Empty)
        return false;
    _cells[position.row][position.col] = symbol;
    return true;
}

Cell Board::GetCell(const Point& position) const {
    return _cells[position.row][position.col];
}

bool Board::IsFull() const {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (_cells[r][c] == Cell::Empty)
                return false;
    return true;
}

std::ostream& operator<<(std::ostream& out, const Board& b) {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            Cell cell = b.GetCell({ r, c });
            if (cell == Cell::X) out << " X ";
            else if (cell == Cell::O) out << " O ";
            else out << " . ";
            if (c < 2) out << "|";
        }
        out << "\n";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Board& b) {
    b.Reset();
    return in;
}