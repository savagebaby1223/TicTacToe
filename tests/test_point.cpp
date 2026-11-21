/**
 * @file test_point.cpp
 * @brief Teste pentru structura Point.
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#include <sstream>
#include "test_framework.hpp"
#include "../point.hpp"

TEST(Point_ConstructorImplicitEsteOrigine) {
    Point p;
    CHECK_EQ(p.row, 0);
    CHECK_EQ(p.col, 0);
}

TEST(Point_ConstructorCuParametri) {
    Point p(2, 1);
    CHECK_EQ(p.row, 2);
    CHECK_EQ(p.col, 1);
}

TEST(Point_Egalitate) {
    CHECK(Point(1, 2) == Point(1, 2));
    CHECK(!(Point(1, 2) == Point(2, 1)));
    CHECK(Point(1, 2) != Point(2, 1));
    CHECK(Point(0, 0) != Point(0, 1));
    CHECK(!(Point(1, 1) != Point(1, 1)));
}

TEST(Point_Afisare) {
    std::ostringstream out;
    out << Point(1, 2);
    CHECK_EQ(out.str(), std::string("(1, 2)"));
}

TEST(Point_CitireCorecta) {
    std::istringstream in("2 0");
    Point p;
    in >> p;
    CHECK(!in.fail());
    CHECK(p == Point(2, 0));
}

TEST(Point_CitireInvalidaSeteazaEroare) {
    std::istringstream in("a b");
    Point p;
    in >> p;
    CHECK(in.fail());
}
