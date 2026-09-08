#include "game_engine.hpp"

GameEngine::GameEngine() {
    _currentPlayer = 0;
}

void GameEngine::Init() {
    _board.Reset();
    _players[0] = Player(Cell::X);
    _players[1] = Player(Cell::O);
    _currentPlayer = 0;
}

void GameEngine::Run() {
    // bucla principala a jocului va fi implementata aici
}

bool GameEngine::MakeMove(const Point& position) {
    Cell symbol = _players[_currentPlayer].GetSymbol();
    return _board.PlaceSymbol(position, symbol);
}

void GameEngine::SwitchPlayer() {
    if (_currentPlayer == 0) {
        _currentPlayer = 1;
    }
    else {
        _currentPlayer = 0;
    }
}

Cell GameEngine::CheckWinner() const {
    // verifica randurile
    for (int r = 0; r < 3; r++) {
        Cell first = _board.GetCell({ r, 0 });
        if (first != Cell::Empty &&
            first == _board.GetCell({ r, 1 }) &&
            first == _board.GetCell({ r, 2 })) {
            return first;
        }
    }
    // verifica coloanele
    for (int c = 0; c < 3; c++) {
        Cell first = _board.GetCell({ 0, c });
        if (first != Cell::Empty &&
            first == _board.GetCell({ 1, c }) &&
            first == _board.GetCell({ 2, c })) {
            return first;
        }
    }
    // verifica diagonala principala
    Cell d1 = _board.GetCell({ 0, 0 });
    if (d1 != Cell::Empty &&
        d1 == _board.GetCell({ 1, 1 }) &&
        d1 == _board.GetCell({ 2, 2 })) {
        return d1;
    }
    // verifica diagonala secundara
    Cell d2 = _board.GetCell({ 0, 2 });
    if (d2 != Cell::Empty &&
        d2 == _board.GetCell({ 1, 1 }) &&
        d2 == _board.GetCell({ 2, 0 })) {
        return d2;
    }
    // nimeni nu a castigat inca
    return Cell::Empty;
}