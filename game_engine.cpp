#include "game_engine.hpp"
#include "human_player.hpp"
#include "computer_player.hpp"
#include <iostream>
#include <thread>
#include <chrono>

GameEngine::GameEngine() : _scores("results.db"), _currentPlayer(0), _mode(1), _delayMs(0) {}

void GameEngine::Init() {
    _board.Reset();
    _currentPlayer = 0;
    _scores.Init();   // creeaza tabelul in baza de date daca nu exista

    // intreaba modul de joc
    std::cout << "Alege modul de joc:\n";
    std::cout << "  1 - Un jucator (contra calculatorului)\n";
    std::cout << "  2 - Doi jucatori\n";
    std::cout << "  3 - Calculator contra calculator\n";
    std::cout << "Optiunea: ";
    if (!(std::cin >> _mode) || _mode < 1 || _mode > 3) _mode = 1;

    // jucatorii sunt creati cu smart pointers, in functie de modul ales
    if (_mode == 1) {
        _players[0] = std::make_unique<HumanPlayer>(Cell::X);
        _players[1] = std::make_unique<ComputerPlayer>(Cell::O);
        _names[0] = "Jucatorul (X)";
        _names[1] = "Calculatorul (O)";
        _delayMs = 0;
    } else if (_mode == 2) {
        _players[0] = std::make_unique<HumanPlayer>(Cell::X);
        _players[1] = std::make_unique<HumanPlayer>(Cell::O);
        _names[0] = "Jucatorul 1 (X)";
        _names[1] = "Jucatorul 2 (O)";
        _delayMs = 0;
    } else {
        _players[0] = std::make_unique<ComputerPlayer>(Cell::X);
        _players[1] = std::make_unique<ComputerPlayer>(Cell::O);
        _names[0] = "Calculatorul 1 (X)";
        _names[1] = "Calculatorul 2 (O)";
        _delayMs = 1000;   // o secunda intre mutari, ca sa se vada jocul
    }
}

void GameEngine::SwitchPlayer() {
    _currentPlayer = (_currentPlayer + 1) % 2;
}

GameResult GameEngine::CheckResult() const {
    Cell winner = _board.GetWinner();
    if (winner == Cell::X) return GameResult::XWins;
    if (winner == Cell::O) return GameResult::OWins;
    // nimeni nu a castigat: daca tabla e plina -> remiza, altfel jocul continua
    if (_board.IsFull()) return GameResult::Draw;
    return GameResult::None;
}

void GameEngine::Run() {
    GameResult result = GameResult::None;

    while (result == GameResult::None) {
        _painter.ClearScreen();
        _painter.DrawBoard(_board);
        _painter.WriteMessage("Este randul: " + _names[_currentPlayer]);

        // polimorfism: motorul nu stie daca jucatorul e om sau calculator
        const Player& current = *_players[_currentPlayer];

        Point move = current.GetMove(_board);
        if (!_board.PlaceSymbol(move, current.GetSymbol())) {
            _painter.WriteMessage("Mutare invalida, incearca din nou.");
            continue;   // nu schimba jucatorul, repeta
        }

        // pauza pe firul de executie, ca mutarea sa poata fi urmarita
        if (_delayMs > 0) {
            _painter.ClearScreen();
            _painter.DrawBoard(_board);
            std::this_thread::sleep_for(std::chrono::milliseconds(_delayMs));
        }

        result = CheckResult();
        if (result == GameResult::None) {
            SwitchPlayer();
        }
    }

    _painter.ClearScreen();
    _painter.DrawBoard(_board);

    if (result == GameResult::XWins)      _painter.WriteMessage("A castigat " + _names[0] + "!");
    else if (result == GameResult::OWins) _painter.WriteMessage("A castigat " + _names[1] + "!");
    else                                  _painter.WriteMessage("Remiza!");

    // salveaza rezultatul in baza de date SQLite si afiseaza istoricul
    _scores.SaveResult(result, _mode);
    _scores.PrintHistory();
}
