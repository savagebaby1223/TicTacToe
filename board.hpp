/**
 * @file board.hpp
 * @brief Tabla de joc 3x3.
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#pragma once

#include <array>
#include <iostream>
#include "cell.hpp"
#include "point.hpp"

/**
 * @brief Tabla de joc: 3 randuri x 3 coloane de casute.
 *
 * Pastreaza continutul casutelor si aplica regulile care tin de tabla:
 * o mutare este acceptata doar pe o casuta valida si libera, tabla poate fi
 * golita, se poate verifica daca este plina si cine a aliniat trei simboluri.
 */
class Board {
    /// continutul casutelor, indexat [rand][coloana]
    std::array<std::array<Cell, 3>, 3> _cells;
public:
    /** @brief Construieste o tabla goala. */
    Board();

    /** @brief Goleste toate casutele (pentru o partida noua). */
    void Reset();

    /**
     * @brief Pune un simbol pe tabla.
     * @param position pozitia casutei
     * @param symbol simbolul pus (Cell::X sau Cell::O)
     * @return true daca mutarea a fost facuta; false daca pozitia este in afara
     *         tablei sau casuta este deja ocupata (tabla ramane neschimbata)
     */
    bool PlaceSymbol(const Point& position, Cell symbol);

    /**
     * @brief Citeste continutul unei casute.
     * @param position pozitia casutei
     * @return continutul casutei; Cell::Empty pentru o pozitie invalida
     */
    Cell GetCell(const Point& position) const;

    /**
     * @brief Verifica daca toate casutele sunt ocupate.
     * @return true daca nu mai exista nicio casuta libera
     */
    bool IsFull() const;

    /**
     * @brief Verifica daca o pozitie se afla pe tabla.
     * @param position pozitia verificata
     * @return true daca randul si coloana sunt intre 0 si 2
     */
    bool IsValid(const Point& position) const;

    /**
     * @brief Determina castigatorul.
     *
     * Verifica cele 8 linii posibile: 3 randuri, 3 coloane si 2 diagonale.
     * @return simbolul care are trei casute in linie (Cell::X sau Cell::O),
     *         sau Cell::Empty daca nu a castigat nimeni
     */
    Cell GetWinner() const;
};

/**
 * @brief Afiseaza tabla in consola, rand cu rand (casutele libere apar ca ".").
 * @param out fluxul de iesire
 * @param b tabla afisata
 * @return fluxul de iesire, pentru inlantuire
 */
std::ostream& operator<<(std::ostream& out, const Board& b);
