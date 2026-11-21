/**
 * @file cell.hpp
 * @brief Starea unei casute de pe tabla de joc.
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#pragma once

/**
 * @brief Continutul unei casute de pe tabla.
 *
 * O casuta poate fi goala sau ocupata de simbolul unuia dintre cei doi jucatori.
 * Acelasi tip este folosit si pentru simbolul unui jucator (X sau O).
 */
enum class Cell {
    Empty, ///< casuta libera
    X,     ///< casuta ocupata cu X
    O      ///< casuta ocupata cu O
};
