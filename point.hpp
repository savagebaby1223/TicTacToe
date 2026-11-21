/**
 * @file point.hpp
 * @brief Pozitia unei casute pe tabla de joc.
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#pragma once

#include <iostream>

/**
 * @brief O pozitie pe tabla, data prin rand si coloana.
 *
 * Pe o tabla 3x3 pozitiile valide au @c row si @c col intre 0 si 2.
 * Structura nu verifica singura validitatea; acest lucru il face Board::IsValid().
 */
struct Point {
    int row; ///< randul (0 = sus)
    int col; ///< coloana (0 = stanga)

    /** @brief Construieste pozitia (0, 0). */
    Point();

    /**
     * @brief Construieste o pozitie data.
     * @param row randul
     * @param col coloana
     */
    Point(int row, int col);

    /**
     * @brief Compara doua pozitii.
     * @param other pozitia cu care se compara
     * @return true daca randul si coloana sunt egale
     */
    bool operator==(const Point& other) const;

    /**
     * @brief Verifica daca doua pozitii difera.
     * @param other pozitia cu care se compara
     * @return true daca difera randul sau coloana
     */
    bool operator!=(const Point& other) const;
};

/**
 * @brief Afiseaza pozitia in forma "(rand, coloana)".
 * @param out fluxul de iesire
 * @param p pozitia afisata
 * @return fluxul de iesire, pentru inlantuire
 */
std::ostream& operator<<(std::ostream& out, const Point& p);

/**
 * @brief Citeste o pozitie ca doua numere intregi: randul, apoi coloana.
 * @param in fluxul de intrare
 * @param p pozitia in care se scrie rezultatul
 * @return fluxul de intrare; in caz de eroare are setat failbit
 */
std::istream& operator>>(std::istream& in, Point& p);
