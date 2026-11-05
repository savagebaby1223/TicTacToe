# Laborator 5 — Crearea și utilizarea modulelor / bibliotecilor

Acest fișier conține interacțiunea cu asistentul AI (LLM) folosit la realizarea laboratorului: prompturile utilizate și răspunsurile generate, în ordine.

Laboratorul continuă proiectul **Tic-tac-toe** din laboratoarele anterioare și se desfășoară în ramura `lab05`.

---

## Prompt: Cerințele Lab 5

> Cerințele lab05: pentru fiecare clasă ce reprezintă datele creați o bibliotecă de
> programare, statică sau dinamică; utilizați biblioteci externe pentru desenarea graficii
> sau pentru păstrarea datelor; rescrieți fișierul de construire astfel încât aplicația să
> utilizeze aceste biblioteci. Fă ce se cere, dar doar ce are sens și afectează logica
> jocului.

### Răspuns

Plan:

1. **Bibliotecă statică proprie** — clasele jocului se compilează în `libgame.a`.
   `main.cpp` rămâne programul care folosește biblioteca. Așa „motorul jocului" devine
   o bibliotecă reutilizabilă, separată de programul care îl rulează.
2. **Bibliotecă externă SQLite** — pentru păstrarea datelor: rezultatul fiecărei partide
   se salvează într-o bază de date, iar la final se afișează istoricul. Are rost real în
   joc (statistica partidelor), nu e pusă artificial.
3. **Makefile rescris** — întâi construiește `libgame.a`, apoi leagă aplicația de ea
   (`-L. -lgame`) și de SQLite (`-lsqlite3`).

---

## Prompt: Tipul bibliotecii

> Ce fel de bibliotecă creezi? / Ce bibliotecă externă folosim?

### Răspuns

- Bibliotecă **statică** (`.a`) — se leagă în executabil la compilare, merge garantat cu
  g++/make, fără probleme de PATH pentru `.dll` pe Windows.
- Bibliotecă externă: **SQLite** — o bibliotecă externă reală, disponibilă în MSYS2,
  folosită pentru păstrarea datelor (istoricul partidelor).

---

## Fișiere noi

### `score_store.hpp`

```cpp
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
```

### `score_store.cpp` (folosește API-ul SQLite)

```cpp
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
```

---

## Fișiere modificate

### `game_engine.hpp`

Motorul are acum un obiect `ScoreStore` și reține modul de joc.

```cpp
#pragma once

#include <memory>
#include "board.hpp"
#include "player.hpp"
#include "painter.hpp"
#include "game_result.hpp"
#include "score_store.hpp"

class GameEngine {
    Board _board;
    // smart pointers in loc de pointeri bruti / alocare manuala
    std::unique_ptr<Player> _players[2];
    Painter _painter;
    ScoreStore _scores;   // pastreaza rezultatele in SQLite
    int _currentPlayer;
    int _mode;            // 1 = contra calculatorului, 2 = doi jucatori
public:
    GameEngine();

    void Init();
    void Run();                       // bucla principala a jocului
    GameResult CheckResult() const;   // X castiga / O castiga / remiza / inca se joaca
    void SwitchPlayer();
};
```

### `game_engine.cpp`

Inițializează baza de date, reține modul de joc și, la final, salvează rezultatul și afișează istoricul.

```cpp
#include "game_engine.hpp"
#include "human_player.hpp"
#include "computer_player.hpp"
#include <iostream>

GameEngine::GameEngine() : _scores("results.db"), _currentPlayer(0), _mode(1) {}

void GameEngine::Init() {
    _board.Reset();
    _currentPlayer = 0;
    _scores.Init();   // creeaza tabelul in baza de date daca nu exista

    // intreaba modul de joc
    int mode = 0;
    std::cout << "Alege modul de joc:\n";
    std::cout << "  1 - Un jucator (contra calculatorului)\n";
    std::cout << "  2 - Doi jucatori\n";
    std::cout << "Optiunea: ";
    std::cin >> mode;
    _mode = (mode == 2) ? 2 : 1;

    // jucatorul 1 e mereu om (X)
    _players[0] = std::make_unique<HumanPlayer>(Cell::X);

    // jucatorul 2 depinde de mod
    if (mode == 2) {
        _players[1] = std::make_unique<HumanPlayer>(Cell::O);
    } else {
        _players[1] = std::make_unique<ComputerPlayer>(Cell::O);
    }
}

void GameEngine::SwitchPlayer() {
    _currentPlayer = (_currentPlayer + 1) % 2;
}

GameResult GameEngine::CheckResult() const {
    for (int i = 0; i < 3; i++) {
        Cell r = _board.GetCell({ i, 0 });
        if (r != Cell::Empty && r == _board.GetCell({ i,1 }) && r == _board.GetCell({ i,2 }))
            return (r == Cell::X) ? GameResult::XWins : GameResult::OWins;
        Cell c = _board.GetCell({ 0, i });
        if (c != Cell::Empty && c == _board.GetCell({ 1,i }) && c == _board.GetCell({ 2,i }))
            return (c == Cell::X) ? GameResult::XWins : GameResult::OWins;
    }
    Cell d1 = _board.GetCell({ 0,0 });
    if (d1 != Cell::Empty && d1 == _board.GetCell({ 1,1 }) && d1 == _board.GetCell({ 2,2 }))
        return (d1 == Cell::X) ? GameResult::XWins : GameResult::OWins;
    Cell d2 = _board.GetCell({ 0,2 });
    if (d2 != Cell::Empty && d2 == _board.GetCell({ 1,1 }) && d2 == _board.GetCell({ 2,0 }))
        return (d2 == Cell::X) ? GameResult::XWins : GameResult::OWins;

    if (_board.IsFull()) return GameResult::Draw;
    return GameResult::None;
}

void GameEngine::Run() {
    GameResult result = GameResult::None;

    while (result == GameResult::None) {
        _painter.ClearScreen();
        _painter.DrawBoard(_board);

        const Player& current = *_players[_currentPlayer];

        Point move = current.GetMove(_board);
        if (!_board.PlaceSymbol(move, current.GetSymbol())) {
            _painter.WriteMessage("Mutare invalida, incearca din nou.");
            continue;
        }

        result = CheckResult();
        if (result == GameResult::None) {
            SwitchPlayer();
        }
    }

    _painter.ClearScreen();
    _painter.DrawBoard(_board);

    if (result == GameResult::XWins)      _painter.WriteMessage("A castigat X!");
    else if (result == GameResult::OWins) _painter.WriteMessage("A castigat O!");
    else                                  _painter.WriteMessage("Remiza!");

    // salveaza rezultatul in baza de date SQLite si afiseaza istoricul
    _scores.SaveResult(result, _mode);
    _scores.PrintHistory();
}
```

### `Makefile` (bibliotecă statică + SQLite)

```makefile
# Compilator si optiuni
CXX      = g++
CXXFLAGS = -std=c++14 -Wall

# Fisierele obiect ale bibliotecii de joc (clasele de date si logica)
LIB_OBJS = point.o board.o player.o human_player.o computer_player.o painter.o score_store.o game_engine.o

# Biblioteca statica proprie
LIB = libgame.a

all: TicTacToe

# 1. Construieste biblioteca statica din clasele jocului
$(LIB): $(LIB_OBJS)
	ar rcs $(LIB) $(LIB_OBJS)

# 2. Leaga aplicatia de biblioteca proprie (-lgame) si de biblioteca externa SQLite (-lsqlite3)
TicTacToe: main.o $(LIB)
	$(CXX) -o TicTacToe.exe main.o -L. -lgame -lsqlite3

point.o: point.cpp point.hpp
	$(CXX) $(CXXFLAGS) -c point.cpp -o point.o

board.o: board.cpp board.hpp
	$(CXX) $(CXXFLAGS) -c board.cpp -o board.o

player.o: player.cpp player.hpp
	$(CXX) $(CXXFLAGS) -c player.cpp -o player.o

human_player.o: human_player.cpp human_player.hpp
	$(CXX) $(CXXFLAGS) -c human_player.cpp -o human_player.o

computer_player.o: computer_player.cpp computer_player.hpp
	$(CXX) $(CXXFLAGS) -c computer_player.cpp -o computer_player.o

painter.o: painter.cpp painter.hpp
	$(CXX) $(CXXFLAGS) -c painter.cpp -o painter.o

score_store.o: score_store.cpp score_store.hpp
	$(CXX) $(CXXFLAGS) -c score_store.cpp -o score_store.o

game_engine.o: game_engine.cpp game_engine.hpp
	$(CXX) $(CXXFLAGS) -c game_engine.cpp -o game_engine.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm -f *.o *.a *.exe

.PHONY: all clean
```

### `.gitignore`

Adăugat `*.a` (biblioteca generată). Baza de date `*.db` era deja ignorată.

---

## Prompt: Compilarea

> Compilează și verifică dacă merge.

### Răspuns

Instalarea SQLite în MSYS2 MINGW64 (o singură dată):

```
pacman -S mingw-w64-x86_64-sqlite3
```

Construirea:

```
make clean
make
```

Ce face `make`:

```
g++ -std=c++14 -Wall -c point.cpp -o point.o
...
ar rcs libgame.a point.o board.o player.o human_player.o computer_player.o painter.o score_store.o game_engine.o
g++ -o TicTacToe.exe main.o -L. -lgame -lsqlite3
```

Testul: după fiecare partidă se afișează istoricul, care crește la fiecare joc:

```
A castigat X!

--- Istoric partide ---
1. X a castigat (mod 2) - 2026-11-05 15:46:35
2. X a castigat (mod 2) - 2026-11-05 15:46:35
```

---

## Concepte explicate (pentru apărare)

- **Bibliotecă statică (`.a`)** — o arhivă de fișiere obiect, creată cu `ar rcs`. Codul ei
  se copiază în executabil la linkare, deci executabilul nu mai are nevoie de ea la rulare.
- **Bibliotecă dinamică (`.dll` / `.so`)** — se încarcă la rulare; executabilul are nevoie
  de fișierul bibliotecii lângă el. Am ales statică pentru simplitate și siguranță.
- **`ar rcs`** — `r` adaugă/înlocuiește fișierele în arhivă, `c` o creează, `s` scrie
  indexul simbolurilor.
- **`-L.`** — caută biblioteci în directorul curent. **`-lgame`** — leagă `libgame.a`
  (prefixul `lib` și extensia se pun automat).
- **`-lsqlite3`** — leagă biblioteca externă SQLite.
- **SQLite** — bază de date într-un singur fișier (`results.db`), fără server.
  Funcții folosite: `sqlite3_open`, `sqlite3_exec`, `sqlite3_prepare_v2`, `sqlite3_bind_*`,
  `sqlite3_step`, `sqlite3_finalize`, `sqlite3_close`.
- **Interogări parametrizate (`?` + `sqlite3_bind_*`)** — valorile se trimit separat de
  comanda SQL, ceea ce previne erorile și injecția SQL.
- **De ce are sens** — motorul jocului devine o bibliotecă reutilizabilă, iar rezultatele
  partidelor sunt păstrate între rulări (istoric real), nu se pierd la închiderea jocului.
