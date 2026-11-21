/**
 * @file test_board.cpp
 * @brief Teste pentru clasa Board (regulile tablei de joc).
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#include <sstream>
#include "test_framework.hpp"
#include "../board.hpp"

/// Umple tabla cu un model dat ca 9 caractere: 'X', 'O' sau '.' (gol).
static Board MakeBoard(const std::string& cells) {
    Board b;
    for (int i = 0; i < 9; i++) {
        if (cells[i] == 'X') b.PlaceSymbol({ i / 3, i % 3 }, Cell::X);
        if (cells[i] == 'O') b.PlaceSymbol({ i / 3, i % 3 }, Cell::O);
    }
    return b;
}

TEST(Board_TablaNouaEsteGoala) {
    Board b;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            CHECK(b.GetCell({ r, c }) == Cell::Empty);
    CHECK(!b.IsFull());
    CHECK(b.GetWinner() == Cell::Empty);
}

TEST(Board_PozitiiValide) {
    Board b;
    CHECK(b.IsValid({ 0, 0 }));
    CHECK(b.IsValid({ 2, 2 }));
    CHECK(b.IsValid({ 1, 2 }));
    CHECK(!b.IsValid({ -1, 0 }));
    CHECK(!b.IsValid({ 0, -1 }));
    CHECK(!b.IsValid({ 3, 0 }));
    CHECK(!b.IsValid({ 0, 3 }));
}

TEST(Board_PlasareSimbol) {
    Board b;
    CHECK(b.PlaceSymbol({ 1, 1 }, Cell::X));
    CHECK(b.GetCell({ 1, 1 }) == Cell::X);
    CHECK(b.GetCell({ 0, 0 }) == Cell::Empty);
}

TEST(Board_CasutaOcupataNuSeSuprascrie) {
    Board b;
    CHECK(b.PlaceSymbol({ 0, 2 }, Cell::X));
    CHECK(!b.PlaceSymbol({ 0, 2 }, Cell::O));
    CHECK(b.GetCell({ 0, 2 }) == Cell::X);
}

TEST(Board_MutareInAfaraTableiEsteRespinsa) {
    Board b;
    CHECK(!b.PlaceSymbol({ 3, 3 }, Cell::X));
    CHECK(!b.PlaceSymbol({ -1, 1 }, Cell::O));
    CHECK(b.GetCell({ 3, 3 }) == Cell::Empty);
}

TEST(Board_ResetGolesteTabla) {
    Board b = MakeBoard("XOXOXOOXO");
    CHECK(b.IsFull());
    b.Reset();
    CHECK(!b.IsFull());
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            CHECK(b.GetCell({ r, c }) == Cell::Empty);
}

TEST(Board_TablaPlina) {
    CHECK(!MakeBoard("XOXOXOOX.").IsFull());
    CHECK(MakeBoard("XOXOXOOXO").IsFull());
}

TEST(Board_CastigPeRanduri) {
    CHECK(MakeBoard("XXX" "OO." "...").GetWinner() == Cell::X);
    CHECK(MakeBoard("XX." "OOO" "X..").GetWinner() == Cell::O);
    CHECK(MakeBoard("OO." "..." "XXX").GetWinner() == Cell::X);
}

TEST(Board_CastigPeColoane) {
    CHECK(MakeBoard("XO." "XO." "X..").GetWinner() == Cell::X);
    CHECK(MakeBoard("XO." "XO." ".OX").GetWinner() == Cell::O);
    CHECK(MakeBoard("O.X" "O.X" "..X").GetWinner() == Cell::X);
}

TEST(Board_CastigPeDiagonale) {
    CHECK(MakeBoard("XO." "OX." "..X").GetWinner() == Cell::X);
    CHECK(MakeBoard("X.O" "XO." "O..").GetWinner() == Cell::O);
}

TEST(Board_FaraCastigator) {
    CHECK(MakeBoard("XX." "OO." "...").GetWinner() == Cell::Empty);
    // remiza: tabla plina fara trei in linie
    Board draw = MakeBoard("XOX" "XOO" "OXX");
    CHECK(draw.IsFull());
    CHECK(draw.GetWinner() == Cell::Empty);
}

TEST(Board_Afisare) {
    std::ostringstream out;
    out << MakeBoard("X.." ".O." "...");
    CHECK_EQ(out.str(), std::string(
        " X | . | . \n"
        "---+---+---\n"
        " . | O | . \n"
        "---+---+---\n"
        " . | . | . \n"));
}
