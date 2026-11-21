/**
 * @file human_player.hpp
 * @brief Jucatorul uman.
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#pragma once

#include "player.hpp"

/**
 * @brief Jucator care isi introduce mutarile de la tastatura.
 */
class HumanPlayer : public Player {
public:
    /**
     * @brief Construieste un jucator uman.
     * @param symbol simbolul cu care joaca
     */
    HumanPlayer(Cell symbol);

    /**
     * @brief Citeste mutarea de la intrarea standard (rand si coloana, 0-2).
     *
     * Daca nu se introduc doua numere, mesajul se repeta pana la o citire
     * corecta. La sfarsitul intrarii (EOF) programul se opreste.
     * @param board tabla curenta
     * @return pozitia introdusa (poate fi ocupata sau in afara tablei;
     *         GameEngine o respinge in acest caz si cere alta)
     */
    Point GetMove(const Board& board) const override;
};
