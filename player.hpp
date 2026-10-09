#pragma once

#include <iostream>
#include "cell.hpp"

class Player {
	Cell _symbol;
public:
	// constructor implicit
	Player();
	// constructor cu parametri
	Player(Cell symbol);
	// constructor de copiere
	Player(const Player& other);
	// operator de atribuire
	Player& operator=(const Player& other);
	// operatori de comparare
	bool operator==(const Player& other) const;
	bool operator!=(const Player& other) const;

	Cell GetSymbol() const;
};

std::ostream& operator<<(std::ostream& out, const Player& p);
std::istream& operator>>(std::istream& in, Player& p);