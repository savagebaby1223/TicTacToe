#pragma once

#include "cell.hpp"

class Player {
	Cell _symbol;
public:
	Player();
	Player(Cell symbol);
	Cell GetSymbol() const;
};