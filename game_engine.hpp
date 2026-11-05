#pragma once

#include <memory>
#include "board.hpp"
#include "player.hpp"
#include "painter.hpp"
#include "game_result.hpp"
#include "score_store.hpp"

class GameEngine {
    Board _board;
    // smart pointers in loc de pointeri bruti / alocare manuala
    std::unique_ptr<Player> _players[2];
    Painter _painter;
    ScoreStore _scores;   // pastreaza rezultatele in SQLite
    int _currentPlayer;
    int _mode;            // 1 = contra calculatorului, 2 = doi jucatori
public:
    GameEngine();

    void Init();
    void Run();                       // bucla principala a jocului
    GameResult CheckResult() const;   // X castiga / O castiga / remiza / inca se joaca
    void SwitchPlayer();
};
