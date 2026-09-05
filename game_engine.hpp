#pragma once

#include "board.hpp"
#include "player.hpp"
#include "point.hpp"
#include "cell.hpp"

class GameEngine {
	Board _board;
	Player _players[2];
	int _currentPlayer;
public:
	GameEngine();
	void Init();
	void Run();
	bool MakeMove(const Point& position);
	Cell CheckWinner() const;
	void SwitchPlayer();
};