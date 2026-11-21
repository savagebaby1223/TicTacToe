/**
 * @file painter.hpp
 * @brief Afisarea jocului in consola.
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#pragma once

#include <string>
#include "board.hpp"
#include "drawable.hpp"

/**
 * @brief Afiseaza tabla si mesajele jocului la iesirea standard.
 *
 * Doar afiseaza si nu modifica starea jocului, de aceea toate metodele sunt const.
 */
class Painter : public Drawable {
public:
    /**
     * @brief Afiseaza tabla.
     * @param board tabla afisata
     */
    void DrawBoard(const Board& board) const override;

    /**
     * @brief Afiseaza un mesaj pe un rand nou.
     * @param text textul afisat
     */
    void WriteMessage(const std::string& text) const;

    /** @brief "Curata" ecranul, afisand randuri goale. */
    void ClearScreen() const;
};
