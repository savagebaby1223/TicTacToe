/**
 * @file test_framework.hpp
 * @brief Cadru minimal de testare unitara, fara dependente externe.
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 *
 * Un test se defineste cu macro-ul TEST(nume) si se inregistreaza automat.
 * In interiorul testului se folosesc CHECK(conditie) si CHECK_EQ(a, b).
 * RunAllTests() ruleaza toate testele si intoarce numarul de teste picate.
 */
#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace test {

/** @brief Un test inregistrat: nume si functia care il ruleaza. */
struct TestCase {
    std::string name;          ///< numele testului
    std::function<void()> fn;  ///< corpul testului
};

/** @brief Lista globala a testelor inregistrate. */
inline std::vector<TestCase>& Registry() {
    static std::vector<TestCase> tests;
    return tests;
}

/** @brief Numarul de verificari esuate in testul curent. */
inline int& CurrentFailures() {
    static int failures = 0;
    return failures;
}

/** @brief Inregistreaza un test la pornirea programului (folosit de TEST). */
struct Registrar {
    /**
     * @param name numele testului
     * @param fn corpul testului
     */
    Registrar(const std::string& name, std::function<void()> fn) {
        Registry().push_back({ name, fn });
    }
};

/**
 * @brief Raporteaza o verificare esuata.
 * @param file fisierul sursa
 * @param line linia din fisier
 * @param expr expresia care nu a fost adevarata
 */
inline void Fail(const char* file, int line, const std::string& expr) {
    ++CurrentFailures();
    std::cout << "    ESUAT: " << expr << "  (" << file << ":" << line << ")\n";
}

/**
 * @brief Ruleaza toate testele inregistrate si afiseaza rezultatul fiecaruia.
 * @return numarul de teste picate (0 = toate au trecut)
 */
inline int RunAllTests() {
    int failedTests = 0;
    for (const TestCase& t : Registry()) {
        CurrentFailures() = 0;
        t.fn();
        bool ok = CurrentFailures() == 0;
        if (!ok) ++failedTests;
        std::cout << (ok ? "[ OK ] " : "[FAIL] ") << t.name << "\n";
    }
    std::cout << "\n" << (Registry().size() - failedTests) << " / "
              << Registry().size() << " teste trecute.\n";
    return failedTests;
}

} // namespace test

/// Defineste si inregistreaza un test.
#define TEST(name)                                                   \
    static void name();                                              \
    static test::Registrar name##_registrar(#name, name);            \
    static void name()

/// Verifica o conditie; daca e falsa, testul este marcat ca esuat.
#define CHECK(cond)                                                  \
    do { if (!(cond)) test::Fail(__FILE__, __LINE__, #cond); } while (0)

/// Verifica egalitatea a doua valori.
#define CHECK_EQ(a, b)                                               \
    do { if (!((a) == (b))) test::Fail(__FILE__, __LINE__, #a " == " #b); } while (0)
