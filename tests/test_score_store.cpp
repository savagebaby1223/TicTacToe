/**
 * @file test_score_store.cpp
 * @brief Teste pentru ScoreStore (salvarea istoricului in SQLite).
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#include <cstdio>
#include <iostream>
#include <sstream>
#include "test_framework.hpp"
#include "../score_store.hpp"

/// Baza de date temporara, folosita doar de teste (nu atinge results.db).
static const char* kTestDb = "tests_results.db";

/// Captureaza tot ce scrie PrintHistory() la iesirea standard.
static std::string CaptureHistory(const ScoreStore& store) {
    std::ostringstream out;
    std::streambuf* old = std::cout.rdbuf(out.rdbuf());
    store.PrintHistory();
    std::cout.rdbuf(old);
    return out.str();
}

/// Numara aparitiile unui text intr-un sir.
static int Count(const std::string& text, const std::string& what) {
    int n = 0;
    for (size_t pos = text.find(what); pos != std::string::npos;
         pos = text.find(what, pos + what.size()))
        ++n;
    return n;
}

TEST(ScoreStore_IstoricGolDupaInit) {
    std::remove(kTestDb);
    ScoreStore store(kTestDb);
    store.Init();
    std::string history = CaptureHistory(store);
    CHECK(history.find("Istoric partide") != std::string::npos);
    CHECK_EQ(Count(history, "(mod "), 0);
    std::remove(kTestDb);
}

TEST(ScoreStore_SalveazaRezultatele) {
    std::remove(kTestDb);
    ScoreStore store(kTestDb);
    store.Init();
    store.SaveResult(GameResult::XWins, 1);
    store.SaveResult(GameResult::OWins, 2);
    store.SaveResult(GameResult::Draw, 3);

    std::string history = CaptureHistory(store);
    CHECK_EQ(Count(history, "(mod "), 3);
    CHECK(history.find("1. X a castigat (mod 1)") != std::string::npos);
    CHECK(history.find("2. O a castigat (mod 2)") != std::string::npos);
    CHECK(history.find("3. Remiza (mod 3)") != std::string::npos);
    std::remove(kTestDb);
}

TEST(ScoreStore_DatelePersistaIntreSesiuni) {
    std::remove(kTestDb);
    {
        ScoreStore first(kTestDb);
        first.Init();
        first.SaveResult(GameResult::Draw, 3);
    }
    ScoreStore second(kTestDb);
    second.Init();  // nu trebuie sa stearga datele existente
    second.SaveResult(GameResult::XWins, 1);

    std::string history = CaptureHistory(second);
    CHECK_EQ(Count(history, "(mod "), 2);
    CHECK(history.find("1. Remiza (mod 3)") != std::string::npos);
    CHECK(history.find("2. X a castigat (mod 1)") != std::string::npos);
    std::remove(kTestDb);
}
