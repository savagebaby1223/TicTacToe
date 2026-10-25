#include "game_engine.hpp"
#include "human_player.hpp"
#include "computer_player.hpp"
#include <iostream>

GameEngine::GameEngine() : _currentPlayer(0) {}

void GameEngine::Init() {
    _board.Reset();
    _currentPlayer = 0;

    // intreaba modul de joc
    int mode = 0;
    std::cout << "Alege modul de joc:\n";
    std::cout << "  1 - Un jucator (contra calculatorului)\n";
    std::cout << "  2 - Doi jucatori\n";
    std::cout << "Optiunea: ";
    std::cin >> mode;

    // jucatorul 1 e mereu om (X)
    _players[0] = std::make_unique<HumanPlayer>(Cell::X);

    // jucatorul 2 depinde de mod
    if (mode == 2) {
        _players[1] = std::make_unique<HumanPlayer>(Cell::O);
    } else {
        _players[1] = std::make_unique<ComputerPlayer>(Cell::O);
    }
}

void GameEngine::SwitchPlayer() {
    _currentPlayer = (_currentPlayer + 1) % 2;
}

GameResult GameEngine::CheckResult() const {
    for (int i = 0; i < 3; i++) {
        Cell r = _board.GetCell({ i, 0 });
        if (r != Cell::Empty && r == _board.GetCell({ i,1 }) && r == _board.GetCell({ i,2 }))
            return (r == Cell::X) ? GameResult::XWins : GameResult::OWins;
        Cell c = _board.GetCell({ 0, i });
        if (c != Cell::Empty && c == _board.GetCell({ 1,i }) && c == _board.GetCell({ 2,i }))
            return (c == Cell::X) ? GameResult::XWins : GameResult::OWins;
    }
    Cell d1 = _board.GetCell({ 0,0 });
    if (d1 != Cell::Empty && d1 == _board.GetCell({ 1,1 }) && d1 == _board.GetCell({ 2,2 }))
        return (d1 == Cell::X) ? GameResult::XWins : GameResult::OWins;
    Cell d2 = _board.GetCell({ 0,2 });
    if (d2 != Cell::Empty && d2 == _board.GetCell({ 1,1 }) && d2 == _board.GetCell({ 2,0 }))
        return (d2 == Cell::X) ? GameResult::XWins : GameResult::OWins;

    if (_board.IsFull()) return GameResult::Draw;
    return GameResult::None;
}

void GameEngine::Run() {
    GameResult result = GameResult::None;

    while (result == GameResult::None) {
        _painter.ClearScreen();
        _painter.DrawBoard(_board);

        const Player& current = *_players[_currentPlayer];

        Point move = current.GetMove(_board);
        if (!_board.PlaceSymbol(move, current.GetSymbol())) {
            _painter.WriteMessage("Mutare invalida, incearca din nou.");
            continue;
        }

        result = CheckResult();
        if (result == GameResult::None) {
            SwitchPlayer();
        }
    }

    _painter.ClearScreen();
    _painter.DrawBoard(_board);

    if (result == GameResult::XWins)      _painter.WriteMessage("A castigat X!");
    else if (result == GameResult::OWins) _painter.WriteMessage("A castigat O!");
    else                                  _painter.WriteMessage("Remiza!");
}
