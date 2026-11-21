# TicTacToe

Joc **X și 0** (Tic-tac-toe) în consolă, scris în C++14.

## Descriere

Proiectul implementează jocul clasic X și 0 pe o tablă de 3×3 căsuțe. Se poate juca
în trei moduri: un om contra calculatorului, doi oameni la aceeași tastatură, sau
calculator contra calculator. Calculatorul alege mutările cu algoritmul **minimax**,
deci nu pierde niciodată: câștigă când adversarul greșește, altfel face remiză.

Rezultatul fiecărei partide se salvează într-o bază de date SQLite (`results.db`),
iar la finalul jocului se afișează istoricul tuturor partidelor jucate.

## Regulile jocului

1. Tabla are 9 căsuțe, dispuse pe 3 rânduri și 3 coloane, toate goale la început.
2. Un jucător joacă cu **X**, celălalt cu **O**. **X** mută primul.
3. Jucătorii mută pe rând. La fiecare mutare jucătorul pune simbolul său într-o
   căsuță liberă.
4. O căsuță ocupată nu mai poate fi aleasă. O mutare invalidă (căsuță ocupată sau
   în afara tablei) este respinsă, iar jucătorul alege din nou.
5. Câștigă jucătorul care aliniază primul trei simboluri proprii pe un rând, o
   coloană sau o diagonală.
6. Dacă toate căsuțele sunt ocupate și nimeni nu a aliniat trei simboluri, partida
   se termină la egalitate (**remiză**).

### Moduri de joc

La pornire se alege modul de joc:

| Mod | Descriere |
|-----|-----------|
| `1` | om (X) contra calculator (O) |
| `2` | doi oameni (X și O) |
| `3` | calculator contra calculator, cu o pauză de o secundă după fiecare mutare, ca partida să poată fi urmărită |

O alegere invalidă pornește modul `1`. Mutarea unui om se introduce ca două numere,
rândul și coloana, fiecare între 0 și 2 (de exemplu `1 1` pentru centru):

```
 0,0 | 0,1 | 0,2
-----+-----+-----
 1,0 | 1,1 | 1,2
-----+-----+-----
 2,0 | 2,1 | 2,2
```

## Dependențe

| Componentă | Rol | Versiune folosită |
|------------|-----|-------------------|
| Windows + [MSYS2](https://www.msys2.org/) (terminal MINGW64) | mediul de construire | — |
| Visual Studio Community | editarea codului | — |
| `g++` (MinGW-w64) | compilator C++, standardul C++14 | orice versiune cu suport C++14 |
| `make` | fișierul de construire `Makefile` | GNU Make |
| `ar` (binutils) | crearea bibliotecii statice `libgame.a` | vine cu `g++` |
| SQLite 3 | bibliotecă externă pentru istoricul partidelor | 3.x |
| Doxygen (opțional) | generarea documentației din cod | 1.9 sau mai nou |

Instalarea în terminalul **MSYS2 MINGW64**:

```bash
pacman -S mingw-w64-x86_64-gcc make mingw-w64-x86_64-sqlite3
pacman -S mingw-w64-x86_64-doxygen      # opțional, pentru documentație
```

Pe Linux sunt suficiente pachetele `g++`, `make` și `libsqlite3-dev`.

Testele unitare nu au dependențe externe: folosesc un cadru minimal propriu
(`tests/test_framework.hpp`).

## Construire și rulare

Toate comenzile se dau din directorul proiectului, în terminalul MINGW64:

```bash
cd /c/Users/Ovidiu/source/repos/TicTacToe   # directorul proiectului
make            # construiește jocul
./TicTacToe.exe # pornește jocul
```

`make` compilează clasele jocului în fișiere obiect `.o`, le grupează în biblioteca
statică `libgame.a`, apoi leagă `main.o` de această bibliotecă și de SQLite,
rezultând `TicTacToe.exe`.

| Comandă | Efect |
|---------|-------|
| `make` | construiește jocul (`TicTacToe.exe`) |
| `make test` | construiește și rulează testele unitare |
| `make docs` | generează documentația HTML în `docs/html/index.html` (necesită Doxygen) |
| `make clean` | șterge fișierele generate (obiecte, biblioteci, executabile, documentație) |

## Teste

Testele se află în directorul `tests/` și verifică clasele care reprezintă datele și
logica jocului. Programul de teste se leagă de aceeași bibliotecă `libgame.a` ca jocul,
deci testează exact codul care rulează în joc.

```bash
make test
```

| Fișier | Ce verifică |
|--------|-------------|
| `test_point.cpp` | constructorii `Point`, operatorii `==`, `!=`, `<<`, `>>` și citirea invalidă |
| `test_board.cpp` | tabla goală, poziții valide/invalide, plasarea simbolurilor, căsuțe ocupate, `Reset`, tabla plină, câștig pe rânduri, coloane și diagonale, remiză, afișarea |
| `test_players.cpp` | simbolul jucătorilor; `HumanPlayer` citește mutarea și ignoră intrarea greșită; `ComputerPlayer` câștigă când poate, blochează adversarul, **nu pierde în nicio partidă posibilă** (atât cu X, cât și cu O) și face remiză contra altui calculator |
| `test_score_store.cpp` | salvarea rezultatelor în SQLite, istoricul și păstrarea datelor între sesiuni (pe o bază de date temporară, nu pe `results.db`) |

La final se afișează câte teste au trecut; dacă vreun test pică, `make test` se
termină cu eroare.

## Documentație

Fiecare fișier header conține comentarii Doxygen: metainformații (proiect, autor,
an), descrierea clasei sau a tipului de date și descrierea fiecărei metode
(parametri și valoare returnată). Documentația HTML se generează cu:

```bash
make docs
```

și se deschide din `docs/html/index.html`.

## Structura proiectului

| Fișier | Conținut |
|--------|----------|
| `cell.hpp` | `Cell` — starea unei căsuțe: goală, X sau O |
| `game_result.hpp` | `GameResult` — partidă în desfășurare, câștig X, câștig O, remiză |
| `point.hpp/.cpp` | `Point` — poziție pe tablă (rând, coloană) |
| `board.hpp/.cpp` | `Board` — tabla 3×3: mutări, verificare tablă plină, câștigător |
| `player.hpp/.cpp` | `Player` — clasă de bază abstractă pentru jucători |
| `human_player.hpp/.cpp` | `HumanPlayer` — jucător care introduce mutarea de la tastatură |
| `computer_player.hpp/.cpp` | `ComputerPlayer` — jucător calculator, algoritmul minimax |
| `drawable.hpp` | `Drawable` — interfață pentru afișarea tablei |
| `painter.hpp/.cpp` | `Painter` — afișarea tablei și a mesajelor în consolă |
| `score_store.hpp/.cpp` | `ScoreStore` — istoricul partidelor în SQLite |
| `game_engine.hpp/.cpp` | `GameEngine` — alegerea modului, bucla de joc, rezultatul |
| `main.cpp` | punctul de intrare al jocului |
| `tests/` | testele unitare |
| `Makefile` | construirea jocului, a testelor și a documentației |
| `Doxyfile` | configurarea Doxygen |

## Istoricul laboratoarelor

- **Lab 3 — Constructori și operatori.** Constructori pentru structurile de date,
  operatori de comparare (`==`, `!=`) și de intrare/ieșire (`>>`, `<<`), clasa de bază
  abstractă `Drawable` cu `Painter`.
- **Lab 4 — Biblioteca standard C++.** `std::array` pentru tablă, `std::unique_ptr`
  pentru jucători, `std::string`, fluxuri I/O, algoritmi STL (`std::fill`,
  `std::all_of`, `std::none_of`, `std::max_element`). Interfața `Player` cu
  `HumanPlayer` și `ComputerPlayer` (minimax), remiza, cele trei moduri de joc și pauza
  `std::this_thread::sleep_for` în modul calculator contra calculator.
- **Lab 5 — Biblioteci.** Clasele jocului sunt compilate în biblioteca statică proprie
  `libgame.a`; biblioteca externă SQLite păstrează istoricul partidelor.
- **Lab 6 — Documentație și teste.** Comentarii Doxygen în toate fișierele header,
  `Doxyfile`, README complet, testele unitare din `tests/` și țintele `make test` și
  `make docs`. Testele au scos la iveală o problemă: `Board::GetCell` citea în afara
  tabloului pentru o poziție invalidă; acum întoarce `Cell::Empty`.

## Utilizarea asistentului AI

La laboratoarele 5 și 6 a fost folosit un asistent AI (LLM). Prompturile și
răspunsurile sunt păstrate în fișierele `Lab05.md` și `Lab06.md`.

## Autor

Ovidiu (`savagebaby1223`), 2026.
