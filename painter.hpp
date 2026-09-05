#pragma once

#include "board.hpp"
#include "cell.hpp"
#include "point.hpp"

class Painter {
public:
	void DrawBoard(const Board& board);
	void WriteMessage(const Point& position, const char* text);
	void ClearScreen();
};
