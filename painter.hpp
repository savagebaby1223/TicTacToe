#pragma once

#include <string>
#include "board.hpp"
#include "drawable.hpp"

class Painter : public Drawable {
public:
    void DrawBoard(const Board& board) override;
    void WriteMessage(const std::string& text);
    void ClearScreen();
};
