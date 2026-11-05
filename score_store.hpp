#pragma once

#include <string>
#include "game_result.hpp"

// Salveaza rezultatele partidelor intr-o baza de date SQLite (biblioteca externa).
// Face parte din biblioteca de joc.
class ScoreStore {
    std::string _dbPath;
public:
    ScoreStore(const std::string& dbPath);

    // creeaza tabelul daca nu exista
    void Init();
    // salveaza rezultatul unei partide (castigator + mod de joc)
    void SaveResult(GameResult result, int mode);
    // afiseaza istoricul partidelor jucate
    void PrintHistory() const;
};
