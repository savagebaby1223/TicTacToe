#pragma once

#include <string>
#include "board.hpp"
#include "drawable.hpp"

// componenta de afisare: nu modifica starea jocului, de aceea metodele sunt const
class Painter : public Drawable {
public:
    void DrawBoard(const Board& board) const override;
    void WriteMessage(const std::string& text) const;
    void ClearScreen() const;
};
