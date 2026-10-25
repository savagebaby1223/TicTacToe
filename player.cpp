#include "player.hpp"

Player::Player(Cell symbol) : _symbol(symbol) {}

Cell Player::GetSymbol() const {
    return _symbol;
}
