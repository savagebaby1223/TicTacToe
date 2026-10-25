#pragma once

#include <memory>
#include "board.hpp"
#include "player.hpp"
#include "painter.hpp"
#include "game_result.hpp"

class GameEngine {
    Board _board;
    // smart pointers in loc de pointeri bruti / alocare manuala
    std::unique_ptr<Player> _players[2];
    Painter _painter;
    int _currentPlayer;
public:
    GameEngine();

    void Init();
    void Run();                       // bucla principala a jocului
    GameResult CheckResult() const;   // X castiga / O castiga / remiza / inca se joaca
    void SwitchPlayer();
};
