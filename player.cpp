#include "player.hpp"

Player::Player() {
    _symbol = Cell::Empty;
}

Player::Player(Cell symbol) {
    _symbol = symbol;
}

Player::Player(const Player& other) {
    _symbol = other._symbol;
}

Player& Player::operator=(const Player& other) {
    _symbol = other._symbol;
    return *this;
}

bool Player::operator==(const Player& other) const {
    return _symbol == other._symbol;
}

bool Player::operator!=(const Player& other) const {
    return !(*this == other);
}

Cell Player::GetSymbol() const {
    return _symbol;
}

std::ostream& operator<<(std::ostream& out, const Player& p) {
    Cell s = p.GetSymbol();
    if (s == Cell::X) out << "X";
    else if (s == Cell::O) out << "O";
    else out << ".";
    return out;
}

std::istream& operator>>(std::istream& in, Player& p) {
    char c;
    in >> c;
    if (c == 'X' || c == 'x') p = Player(Cell::X);
    else if (c == 'O' || c == 'o') p = Player(Cell::O);
    else p = Player(Cell::Empty);
    return in;
}