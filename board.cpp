#include "board.hpp"
#include <algorithm>

Board::Board() {
    Reset();
}

void Board::Reset() {
    // algoritm STL std::fill pentru fiecare rand
    for (auto& row : _cells) {
        std::fill(row.begin(), row.end(), Cell::Empty);
    }
}

bool Board::IsValid(const Point& p) const {
    return p.row >= 0 && p.row < 3 && p.col >= 0 && p.col < 3;
}

bool Board::PlaceSymbol(const Point& position, Cell symbol) {
    if (!IsValid(position)) return false;
    if (_cells[position.row][position.col] != Cell::Empty) return false;
    _cells[position.row][position.col] = symbol;
    return true;
}

Cell Board::GetCell(const Point& position) const {
    return _cells[position.row][position.col];
}

bool Board::IsFull() const {
    // algoritm STL std::all_of + std::none_of
    return std::all_of(_cells.begin(), _cells.end(),
        [](const std::array<Cell, 3>& row) {
            return std::none_of(row.begin(), row.end(),
                [](Cell c) { return c == Cell::Empty; });
        });
}

Cell Board::GetWinner() const {
    // cele 8 linii castigatoare: 3 randuri, 3 coloane, 2 diagonale
    static const std::array<std::array<Point, 3>, 8> lines = {{
        {{ {0,0}, {0,1}, {0,2} }}, {{ {1,0}, {1,1}, {1,2} }}, {{ {2,0}, {2,1}, {2,2} }},
        {{ {0,0}, {1,0}, {2,0} }}, {{ {0,1}, {1,1}, {2,1} }}, {{ {0,2}, {1,2}, {2,2} }},
        {{ {0,0}, {1,1}, {2,2} }}, {{ {0,2}, {1,1}, {2,0} }}
    }};
    for (const auto& line : lines) {
        Cell first = GetCell(line[0]);
        // algoritm STL std::all_of: toate cele 3 casute au acelasi simbol
        if (first != Cell::Empty &&
            std::all_of(line.begin(), line.end(),
                [&](const Point& p) { return GetCell(p) == first; })) {
            return first;
        }
    }
    return Cell::Empty;
}

static char ToChar(Cell c) {
    if (c == Cell::X) return 'X';
    if (c == Cell::O) return 'O';
    return '.';
}

std::ostream& operator<<(std::ostream& out, const Board& b) {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            out << ' ' << ToChar(b.GetCell({ r, c })) << ' ';
            if (c < 2) out << '|';
        }
        out << '\n';
        if (r < 2) out << "---+---+---\n";
    }
    return out;
}
