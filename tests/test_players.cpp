/**
 * @file test_players.cpp
 * @brief Teste pentru jucatori: Player, HumanPlayer si ComputerPlayer.
 *
 * Proiect: TicTacToe (X si 0) — joc in consola scris in C++14.
 * @author Ovidiu (savagebaby1223)
 * @date 2026
 */
#include <iostream>
#include <memory>
#include <sstream>
#include "test_framework.hpp"
#include "../board.hpp"
#include "../human_player.hpp"
#include "../computer_player.hpp"

/**
 * @brief Redirectioneaza temporar std::cin si std::cout catre siruri de caractere.
 *
 * Folosit ca testele sa poata "tasta" mutari si sa nu umple consola cu mesajele
 * jucatorilor. La distrugere fluxurile originale sunt refacute.
 */
class ConsoleRedirect {
    std::istringstream _in;
    std::ostringstream _out;
    std::streambuf* _oldIn;
    std::streambuf* _oldOut;
public:
    explicit ConsoleRedirect(const std::string& input = "")
        : _in(input),
          _oldIn(std::cin.rdbuf(_in.rdbuf())),
          _oldOut(std::cout.rdbuf(_out.rdbuf())) {}
    ~ConsoleRedirect() {
        std::cin.rdbuf(_oldIn);
        std::cout.rdbuf(_oldOut);
        std::cin.clear();
    }
    std::string Output() const { return _out.str(); }
};

/// Umple tabla cu un model de 9 caractere: 'X', 'O' sau '.'.
static Board MakeBoard(const std::string& cells) {
    Board b;
    for (int i = 0; i < 9; i++) {
        if (cells[i] == 'X') b.PlaceSymbol({ i / 3, i % 3 }, Cell::X);
        if (cells[i] == 'O') b.PlaceSymbol({ i / 3, i % 3 }, Cell::O);
    }
    return b;
}

static Cell Other(Cell c) { return c == Cell::X ? Cell::O : Cell::X; }

TEST(Player_SimbolulEstePastrat) {
    std::unique_ptr<Player> x = std::make_unique<HumanPlayer>(Cell::X);
    std::unique_ptr<Player> o = std::make_unique<ComputerPlayer>(Cell::O);
    CHECK(x->GetSymbol() == Cell::X);
    CHECK(o->GetSymbol() == Cell::O);
}

TEST(HumanPlayer_CitesteMutarea) {
    ConsoleRedirect console("1 2\n");
    HumanPlayer player(Cell::X);
    Board b;
    Point move = player.GetMove(b);
    CHECK(move == Point(1, 2));
    CHECK(console.Output().find("Jucatorul X") != std::string::npos);
}

TEST(HumanPlayer_IgnoraIntrareaInvalida) {
    ConsoleRedirect console("abc\n0 1\n");
    HumanPlayer player(Cell::O);
    Board b;
    Point move = player.GetMove(b);
    CHECK(move == Point(0, 1));
    CHECK(console.Output().find("Introduceti doua numere") != std::string::npos);
}

TEST(ComputerPlayer_AlegeCasutaLibera) {
    ConsoleRedirect console;
    ComputerPlayer player(Cell::X);
    Board b = MakeBoard("XOX" "OXO" "O..");
    Point move = player.GetMove(b);
    CHECK(b.IsValid(move));
    CHECK(b.GetCell(move) == Cell::Empty);
}

TEST(ComputerPlayer_TablaPlinaNuAreMutare) {
    ConsoleRedirect console;
    ComputerPlayer player(Cell::X);
    Point move = player.GetMove(MakeBoard("XOXXOOOXX"));
    CHECK(move == Point(-1, -1));
}

TEST(ComputerPlayer_CastigaCandPoate) {
    ConsoleRedirect console;
    ComputerPlayer player(Cell::O);
    // O are doua pe coloana din mijloc: castiga in (2,1)
    Board b = MakeBoard("XOX" "XO." "...");
    CHECK(player.GetMove(b) == Point(2, 1));
}

TEST(ComputerPlayer_PreferaCastigulInLoculBlocarii) {
    ConsoleRedirect console;
    ComputerPlayer player(Cell::X);
    // si X, si O pot castiga la mutarea urmatoare; X la rand trebuie sa castige
    Board b = MakeBoard("XX." "OO." "...");
    CHECK(player.GetMove(b) == Point(0, 2));
}

TEST(ComputerPlayer_BlocheazaAdversarul) {
    ConsoleRedirect console;
    ComputerPlayer player(Cell::O);
    // X ameninta randul de sus; O trebuie sa blocheze in (0,2)
    Board b = MakeBoard("XX." ".O." "...");
    CHECK(player.GetMove(b) == Point(0, 2));
}

/**
 * Joaca toate partidele posibile impotriva calculatorului: adversarul incearca
 * pe rand fiecare mutare libera. Daca adversarul castiga macar o data, testul pica.
 */
static void PlayAll(const ComputerPlayer& ai, Board board, Cell toMove,
                    int& games, int& losses) {
    Cell aiSymbol = ai.GetSymbol();
    Cell winner = board.GetWinner();
    if (winner != Cell::Empty || board.IsFull()) {
        ++games;
        if (winner == Other(aiSymbol)) ++losses;
        return;
    }
    if (toMove == aiSymbol) {
        Board next = board;
        next.PlaceSymbol(ai.GetMove(board), aiSymbol);
        PlayAll(ai, next, Other(toMove), games, losses);
    } else {
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++) {
                Board next = board;
                if (next.PlaceSymbol({ r, c }, toMove))
                    PlayAll(ai, next, Other(toMove), games, losses);
            }
    }
}

TEST(ComputerPlayer_NuPierdeNiciodataCaX) {
    ConsoleRedirect console;
    ComputerPlayer ai(Cell::X);
    int games = 0, losses = 0;
    PlayAll(ai, Board(), Cell::X, games, losses);
    CHECK(games > 0);
    CHECK_EQ(losses, 0);
}

TEST(ComputerPlayer_NuPierdeNiciodataCaO) {
    ConsoleRedirect console;
    ComputerPlayer ai(Cell::O);
    int games = 0, losses = 0;
    PlayAll(ai, Board(), Cell::X, games, losses);
    CHECK(games > 0);
    CHECK_EQ(losses, 0);
}

TEST(ComputerPlayer_DoiCalculatoareFacRemiza) {
    ConsoleRedirect console;
    ComputerPlayer x(Cell::X), o(Cell::O);
    for (int game = 0; game < 5; game++) {
        Board b;
        const ComputerPlayer* current = &x;
        while (b.GetWinner() == Cell::Empty && !b.IsFull()) {
            b.PlaceSymbol(current->GetMove(b), current->GetSymbol());
            current = (current == &x) ? &o : &x;
        }
        CHECK(b.GetWinner() == Cell::Empty);
        CHECK(b.IsFull());
    }
}
