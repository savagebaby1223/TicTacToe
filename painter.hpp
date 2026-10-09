#pragma once

#include "board.hpp"
#include "cell.hpp"
#include "point.hpp"
#include "drawable.hpp"

class Painter : public Drawable {
public:
	void DrawBoard(const Board& board) override;
	void WriteMessage(const Point& position, const char* text);
	void ClearScreen();
};