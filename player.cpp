#include "player.hpp" 
Player::Player() { 
    _symbol = Cell::Empty; 
}       

Player::Player(Cell symbol) {  
    _symbol = symbol;
}

Cell Player::GetSymbol() const { 
    return _symbol;
}