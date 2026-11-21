/**
 * @file player.hpp
 * @brief Interfata comuna a jucatorilor.
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#pragma once

#include <iostream>
#include "cell.hpp"
#include "point.hpp"

class Board;  // declaratie anticipata: aici e nevoie doar de o referinta la tabla

/**
 * @brief Clasa de baza abstracta pentru orice jucator.
 *
 * Un jucator are un simbol (X sau O) si stie sa aleaga o mutare pentru o
 * tabla data. Felul in care alege mutarea difera: HumanPlayer o citeste de la
 * tastatura, ComputerPlayer o calculeaza.
 */
class Player {
protected:
    Cell _symbol; ///< simbolul cu care joaca (Cell::X sau Cell::O)
public:
    /**
     * @brief Construieste un jucator.
     * @param symbol simbolul cu care joaca
     */
    Player(Cell symbol);

    /** @brief Destructor virtual, pentru distrugerea corecta prin pointer la baza. */
    virtual ~Player() {}

    /**
     * @brief Simbolul jucatorului.
     * @return Cell::X sau Cell::O
     */
    Cell GetSymbol() const;

    /**
     * @brief Alege urmatoarea mutare.
     * @param board tabla curenta (doar citita, nu modificata)
     * @return pozitia aleasa; validitatea ei este verificata de GameEngine
     */
    virtual Point GetMove(const Board& board) const = 0;
};
