/**
 * @file test_main.cpp
 * @brief Punctul de intrare al programului de teste.
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#include "test_framework.hpp"

/**
 * @brief Ruleaza toate testele.
 * @return 0 daca toate testele au trecut, 1 altfel (pentru make)
 */
int main() {
    return test::RunAllTests() == 0 ? 0 : 1;
}
