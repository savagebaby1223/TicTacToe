/**
 * @file computer_player.hpp
 * @brief Jucatorul controlat de calculator.
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#pragma once

#include "player.hpp"

/**
 * @brief Jucator controlat de calculator, bazat pe algoritmul minimax.
 *
 * Pentru fiecare casuta libera simuleaza toate continuarile posibile ale
 * partidei si alege mutarea cu cel mai bun scor. De aceea nu pierde niciodata:
 * castiga cand adversarul greseste, altfel face remiza. Dintre mutarile la fel
 * de bune alege una la intamplare, ca partidele sa nu fie identice.
 */
class ComputerPlayer : public Player {
    /**
     * @brief Evalueaza o pozitie prin explorarea tuturor mutarilor ramase.
     * @param board pozitia evaluata
     * @param myTurn true daca urmeaza la mutare calculatorul
     * @param depth numarul de mutari simulate pana aici
     * @return 10 - depth daca calculatorul castiga, depth - 10 daca pierde,
     *         0 la remiza (un castig mai rapid are scor mai mare)
     */
    int Minimax(const Board& board, bool myTurn, int depth) const;
public:
    /**
     * @brief Construieste un jucator calculator.
     * @param symbol simbolul cu care joaca
     */
    ComputerPlayer(Cell symbol);

    /**
     * @brief Calculeaza cea mai buna mutare pentru tabla data.
     * @param board tabla curenta
     * @return o casuta libera cu scor minimax maxim, sau (-1, -1) daca tabla
     *         este plina
     */
    Point GetMove(const Board& board) const override;
};
