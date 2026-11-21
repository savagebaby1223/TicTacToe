/**
 * @file game_result.hpp
 * @brief Rezultatul unei partide.
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#pragma once

/**
 * @brief Starea partidei, asa cum o determina GameEngine::CheckResult().
 */
enum class GameResult {
    None,   ///< partida continua (nu exista inca un rezultat)
    XWins,  ///< jucatorul cu X a aliniat trei simboluri
    OWins,  ///< jucatorul cu O a aliniat trei simboluri
    Draw    ///< tabla este plina si nu a castigat nimeni (remiza)
};
