#include "score_store.hpp"
#include <sqlite3.h>
#include <iostream>

ScoreStore::ScoreStore(const std::string& dbPath) : _dbPath(dbPath) {}

static std::string ResultToText(GameResult r) {
    switch (r) {
        case GameResult::XWins: return "X a castigat";
        case GameResult::OWins: return "O a castigat";
        case GameResult::Draw:  return "Remiza";
        default:                return "Neterminat";
    }
}

void ScoreStore::Init() {
    sqlite3* db = nullptr;
    if (sqlite3_open(_dbPath.c_str(), &db) != SQLITE_OK) {
        std::cout << "Eroare la deschiderea bazei de date.\n";
        return;
    }
    const char* sql =
        "CREATE TABLE IF NOT EXISTS results ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "rezultat TEXT, "
        "mod INTEGER, "
        "data TEXT DEFAULT CURRENT_TIMESTAMP);";
    char* err = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &err) != SQLITE_OK) {
        std::cout << "Eroare SQL: " << (err ? err : "") << "\n";
        sqlite3_free(err);
    }
    sqlite3_close(db);
}

void ScoreStore::SaveResult(GameResult result, int mode) {
    sqlite3* db = nullptr;
    if (sqlite3_open(_dbPath.c_str(), &db) != SQLITE_OK) return;

    std::string sql = "INSERT INTO results (rezultat, mod) VALUES (?, ?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        std::string text = ResultToText(result);
        sqlite3_bind_text(stmt, 1, text.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, mode);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

void ScoreStore::PrintHistory() const {
    sqlite3* db = nullptr;
    if (sqlite3_open(_dbPath.c_str(), &db) != SQLITE_OK) return;

    const char* sql = "SELECT id, rezultat, mod, data FROM results ORDER BY id;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        std::cout << "\n--- Istoric partide ---\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* rez = sqlite3_column_text(stmt, 1);
            int mod = sqlite3_column_int(stmt, 2);
            const unsigned char* data = sqlite3_column_text(stmt, 3);
            std::cout << id << ". " << (rez ? (const char*)rez : "")
                      << " (mod " << mod << ") - "
                      << (data ? (const char*)data : "") << "\n";
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}
