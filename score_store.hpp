/**
 * @file score_store.hpp
 * @brief Istoricul partidelor, pastrat in SQLite.
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#pragma once

#include <string>
#include "game_result.hpp"

/**
 * @brief Salveaza rezultatele partidelor intr-o baza de date SQLite.
 *
 * Fiecare partida terminata este un rand in tabelul @c results
 * (id, rezultat, mod de joc, data). Baza de date este un fisier; daca nu
 * poate fi deschisa, operatiile nu fac nimic, iar jocul continua normal.
 */
class ScoreStore {
    std::string _dbPath; ///< calea fisierului bazei de date
public:
    /**
     * @brief Construieste obiectul (nu deschide inca baza de date).
     * @param dbPath calea fisierului bazei de date, de exemplu "results.db"
     */
    ScoreStore(const std::string& dbPath);

    /** @brief Creeaza tabelul @c results, daca nu exista deja. */
    void Init();

    /**
     * @brief Salveaza rezultatul unei partide.
     * @param result rezultatul partidei
     * @param mode modul de joc (1, 2 sau 3)
     */
    void SaveResult(GameResult result, int mode);

    /** @brief Afiseaza toate partidele salvate, in ordinea in care au fost jucate. */
    void PrintHistory() const;
};
