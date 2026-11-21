/**
 * @file game_engine.hpp
 * @brief Motorul jocului: leaga tabla, jucatorii, afisarea si istoricul.
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#pragma once

#include <memory>
#include <string>
#include "board.hpp"
#include "player.hpp"
#include "painter.hpp"
#include "game_result.hpp"
#include "score_store.hpp"

/**
 * @brief Conduce o partida de la alegerea modului de joc pana la rezultat.
 *
 * Moduri de joc:
 * - 1: om (X) contra calculator (O);
 * - 2: doi oameni;
 * - 3: calculator contra calculator, cu o pauza de o secunda dupa fiecare mutare.
 *
 * X muta primul. O mutare invalida este respinsa si jucatorul este intrebat din
 * nou. La final rezultatul este salvat in baza de date si se afiseaza istoricul.
 */
class GameEngine {
    Board _board;                         ///< tabla de joc
    std::unique_ptr<Player> _players[2];  ///< [0] joaca cu X, [1] joaca cu O
    std::string _names[2];                ///< numele afisate ale jucatorilor
    Painter _painter;                     ///< afisarea in consola
    ScoreStore _scores;                   ///< istoricul partidelor (results.db)
    int _currentPlayer;                   ///< indicele jucatorului la rand (0 sau 1)
    int _mode;                            ///< modul de joc (1, 2 sau 3)
    int _delayMs;                         ///< pauza dupa fiecare mutare, in milisecunde
public:
    /** @brief Construieste motorul; baza de date folosita este "results.db". */
    GameEngine();

    /**
     * @brief Pregateste o partida noua.
     *
     * Goleste tabla, initializeaza baza de date, cere modul de joc
     * (o alegere invalida inseamna modul 1) si creeaza jucatorii.
     */
    void Init();

    /** @brief Bucla principala: mutari pe rand pana la castig sau remiza. */
    void Run();

    /**
     * @brief Determina starea partidei pe tabla curenta.
     * @return XWins / OWins daca exista trei simboluri in linie, Draw daca tabla
     *         e plina fara castigator, altfel None
     */
    GameResult CheckResult() const;

    /** @brief Trece randul la celalalt jucator. */
    void SwitchPlayer();
};
