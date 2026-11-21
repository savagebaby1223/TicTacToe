/**
 * @file drawable.hpp
 * @brief Interfata pentru afisarea tablei.
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#pragma once

#include "board.hpp"

/**
 * @brief Clasa de baza abstracta pentru orice componenta care afiseaza tabla.
 */
class Drawable {
public:
    /**
     * @brief Afiseaza tabla.
     * @param board tabla afisata (doar citita)
     */
    virtual void DrawBoard(const Board& board) const = 0;

    /** @brief Destructor virtual. */
    virtual ~Drawable() {}
};
