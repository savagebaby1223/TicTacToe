# Laborator 6 — Suportul proiectului. Elaborarea documentației

Acest fișier conține interacțiunea cu asistentul AI (LLM) folosit la realizarea laboratorului: prompturile utilizate și răspunsurile generate, în ordine.

Laboratorul continuă proiectul **Tic-tac-toe** din laboratoarele anterioare și se desfășoară în ramura `lab06`.

---

## Prompt: Cerințele Lab 6

> Cerințele lab06: lucrați în ramura `lab06`. Adăugați documentația codului sursă cu
> Doxygen sau JavaDoc; fiecare fișier header trebuie să conțină metainformații (numele
> proiectului, autorul, anul etc.), descrierea clasei / tipului de date și descrierea
> metodelor. `README.md` trebuie să conțină descrierea proiectului, regulile jocului,
> dependențele proiectului (mediul de dezvoltare, compilatorul, biblioteci terțe) și
> instrucțiunile de construire. Creați directorul `tests` și scrieți teste pentru
> clasele care reprezintă datele; actualizați fișierul de construire ca să compileze și
> să ruleze testele. Fă-l cum trebuie, doar ce ține de logica jocului.

### Răspuns

Plan:

1. **Documentație Doxygen** în toate cele 11 fișiere header: un bloc `@file` cu
   proiectul, autorul și anul, descrierea fiecărei clase / enumerări și, pentru fiecare
   metodă, `@brief`, `@param` și `@return`. Plus un `Doxyfile` și ținta `make docs`.
2. **Teste** în `tests/` pentru clasele cu date și logică: `Point`, `Board`,
   jucătorii (`HumanPlayer`, `ComputerPlayer`) și `ScoreStore`.
3. **Makefile**: ținta `make test` construiește programul de teste, îl leagă de
   aceeași bibliotecă `libgame.a` ca jocul și îl rulează.
4. **README** rescris pe secțiuni: descriere, reguli, dependențe, construire, teste,
   documentație, structura proiectului.

---

## Prompt: Doxygen sau JavaDoc?

> Ce folosim pentru documentație, Doxygen sau JavaDoc?

### Răspuns

Doxygen — este instrumentul standard pentru C++ (JavaDoc este pentru Java). Doxygen
înțelege și stilul de comentarii JavaDoc (`/** ... */`, `@param`, `@return`), deci
comentariile arată familiar. Exemplu din `board.hpp`:

```cpp
/**
 * @brief Pune un simbol pe tabla.
 * @param position pozitia casutei
 * @param symbol simbolul pus (Cell::X sau Cell::O)
 * @return true daca mutarea a fost facuta; false daca pozitia este in afara
 *         tablei sau casuta este deja ocupata (tabla ramane neschimbata)
 */
bool PlaceSymbol(const Point& position, Cell symbol);
```

Doxygen este o dependență opțională: jocul și testele se construiesc fără el; e
nevoie de el doar pentru `make docs`.

---

## Prompt: Cu ce scriem testele?

> Folosim o bibliotecă de teste (Google Test, Catch2) sau facem altfel?

### Răspuns

Un cadru minimal propriu, `tests/test_framework.hpp` (~80 de linii):

- `TEST(nume)` definește un test și îl înregistrează automat;
- `CHECK(conditie)` și `CHECK_EQ(a, b)` verifică rezultatele și afișează fișierul și
  linia în caz de eșec;
- `test::RunAllTests()` rulează toate testele și întoarce numărul celor picate, iar
  `main` întoarce 1 dacă a picat ceva, ca `make test` să se oprească cu eroare.

Motivul: Google Test sau Catch2 ar fi încă o bibliotecă de instalat în MSYS2, fără
niciun câștig real pentru un proiect de mărimea asta.

---

## Prompt: Ce testăm?

> Ce teste scriem, ca să aibă sens pentru joc?

### Răspuns

Doar comportamentul de care depinde jocul:

- **Point** — constructorii, `==` / `!=`, afișarea `(r, c)`, citirea a două numere și
  citirea invalidă (pe care se bazează `HumanPlayer`).
- **Board** — tabla nouă e goală; `IsValid` acceptă doar 0–2; `PlaceSymbol` pune
  simbolul, nu suprascrie o căsuță ocupată și respinge pozițiile din afara tablei;
  `Reset`; `IsFull`; `GetWinner` pe toate cele 3 rânduri, 3 coloane și 2 diagonale;
  remiza (tablă plină fără câștigător); afișarea tablei.
- **HumanPlayer** — `std::cin` este redirecționat spre un șir de caractere, ca testul
  să „tasteze" mutarea; se verifică și că o intrare greșită (`abc`) e ignorată.
- **ComputerPlayer** — câștigă când poate, preferă câștigul în locul blocării,
  blochează adversarul, nu are mutare pe tabla plină, iar două calculatoare fac
  întotdeauna remiză. Cel mai important test: adversarul încearcă **toate** mutările
  posibile, recursiv, și se verifică că în nicio partidă calculatorul nu pierde (atât
  când joacă cu X, cât și cu O).
- **ScoreStore** — pe o bază de date temporară (`tests_results.db`, ștearsă la final,
  ca să nu strice `results.db`): istoric gol după `Init`, salvarea rezultatelor,
  păstrarea datelor între două obiecte `ScoreStore` (adică între două rulări ale
  jocului).

`GameEngine` și `Painter` nu au teste separate: unul citește de la tastatură modul de
joc și conduce bucla, celălalt doar afișează; logica lor este cea din `Board` și din
jucători, care e deja testată.

---

## Prompt: Problemă găsită de teste

> A picat ceva?

### Răspuns

Testul `Board_MutareInAfaraTableiEsteRespinsa` apelează `GetCell({3, 3})`.
`GetCell` citea direct `_cells[3][3]`, adică în afara tabloului (comportament
nedefinit). Corectura din `board.cpp`:

```cpp
Cell Board::GetCell(const Point& position) const {
    // o pozitie in afara tablei nu are continut: nu citim din afara tabloului
    if (!IsValid(position)) return Cell::Empty;
    return _cells[position.row][position.col];
}
```

Rezultatul final:

```
$ make test
...
32 / 32 teste trecute.
```

---

## Prompt: Makefile

> Cum arată fișierul de construire acum?

### Răspuns

S-au adăugat trei ținte noi; construirea jocului a rămas aceeași:

```make
TEST_OBJS = tests/test_main.o tests/test_point.o tests/test_board.o tests/test_players.o tests/test_score_store.o
TEST_EXE  = tests/run_tests.exe

test: $(TEST_EXE)
	./$(TEST_EXE)

$(TEST_EXE): $(TEST_OBJS) $(LIB)
	$(CXX) -o $(TEST_EXE) $(TEST_OBJS) -L. -lgame -lsqlite3

tests/%.o: tests/%.cpp tests/test_framework.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

docs:
	doxygen Doxyfile
```

Testele se leagă de `libgame.a`, deci verifică exact codul folosit de joc. `make clean`
șterge acum și obiectele testelor și directorul `docs/`. În `.gitignore` au fost
adăugate `docs/` și baza de date temporară a testelor.

---

## Prompt: README

> Refă README-ul ca la carte.

### Răspuns

`README.md` a fost rescris pe secțiuni:

1. **Descriere** — ce este jocul, modurile, minimax, istoricul în SQLite.
2. **Regulile jocului** — cine mută primul, mutări valide, câștig, remiză, cum se
   introduce o mutare (cu schema coordonatelor).
3. **Dependențe** — MSYS2 MINGW64, Visual Studio Community, g++ (C++14), make, `ar`,
   SQLite 3, Doxygen opțional, cu comenzile `pacman` de instalare.
4. **Construire și rulare** — `make`, `./TicTacToe.exe`, `make test`, `make docs`,
   `make clean`.
5. **Teste** — ce verifică fiecare fișier din `tests/`.
6. **Documentație** — cum se generează și unde se deschide.
7. **Structura proiectului**, **istoricul laboratoarelor**, utilizarea asistentului
   AI și autorul.
