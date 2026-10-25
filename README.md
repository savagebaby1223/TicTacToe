# TicTacToe

## Despre proiect

Acest proiect este o implementare a jocului clasic X și 0 (Tic-tac-toe), scrisă în
limbajul C++. Jocul se poate juca în doi (ambii jucători oameni) sau un jucător
contra calculatorului. Se joacă pe o tablă de 3×3 căsuțe, punând pe rând simbolul
(X sau O). Câștigă cel care reușește primul să alinieze trei simboluri identice pe
un rând, o coloană sau o diagonală.

## Cum se joacă

1. La pornire se alege modul: un jucător (contra calculatorului) sau doi jucători.
2. Tabla are 9 căsuțe, dispuse pe 3 rânduri și 3 coloane, toate goale la început.
3. Cei doi jucători mută pe rând: unul joacă cu X, celălalt cu O.
4. La rândul său, un jucător alege o căsuță liberă (introduce rândul și coloana, 0-2)
   și își pune simbolul acolo.
5. O căsuță deja ocupată nu poate fi aleasă din nou.
6. Partida este câștigată de jucătorul care aliniază trei simboluri identice pe
   orizontală, verticală sau diagonală.
7. Dacă toate căsuțele sunt ocupate și nimeni nu a aliniat trei simboluri, partida
   se termină la egalitate (remiză).

## Tipurile de date folosite

- **Point** (`point.hpp`) — o structură care reține o poziție pe tablă, prin rândul
  (`row`) și coloana (`col`) sale.
- **Cell** (`cell.hpp`) — o enumerare ce descrie starea unei căsuțe: goală (Empty),
  ocupată cu X sau ocupată cu O.
- **GameResult** (`game_result.hpp`) — o enumerare ce descrie rezultatul jocului:
  în desfășurare (None), câștig X, câștig O sau remiză (Draw).
- **Player** (`player.hpp`) — clasă de bază abstractă pentru orice jucător; reține
  simbolul și declară metoda virtuală pură `GetMove`.
- **HumanPlayer** (`human_player.hpp`) — jucător uman; citește mutarea de la tastatură.
- **ComputerPlayer** (`computer_player.hpp`) — jucător controlat de calculator; alege
  singur mutarea (câștigă dacă poate, altfel blochează adversarul).
- **Board** (`board.hpp`) — clasa tablei de joc; păstrează conținutul celor 9 căsuțe
  și oferă operații de plasare a simbolurilor, golire și verificare a stării tablei.
- **GameEngine** (`game_engine.hpp`) — motorul jocului; reunește tabla și jucătorii,
  ține evidența jucătorului aflat la rând și aplică regulile (mutări valide, verificarea
  câștigătorului, remiză, schimbarea rândului).
- **Drawable** (`drawable.hpp`) — clasă de bază abstractă pentru redare.
- **Painter** (`painter.hpp`) — componenta de afișare, care desenează tabla pe ecran
  și afișează mesajele către jucători.

## Autor

Ovidiu

## Construirea proiectului

Proiectul este scris în C++ și se compilează cu ajutorul compilatorului `g++`
și al utilitarului `make`.

### Cerințe

- compilatorul MinGW G++
- utilitarul make

### Pași de construire

Deschideți un terminal în directorul proiectului și rulați:

    make

Comanda `make` compilează fiecare fișier sursă `.cpp` într-un fișier obiect `.o`
și apoi le leagă într-un executabil numit `TicTacToe.exe`.

Pentru a șterge fișierele generate (obiecte și executabil), rulați:

    make clean

### Compilare manuală

Alternativ, un singur fișier poate fi compilat într-un fișier obiect astfel:

    g++ board.cpp -o board.o -c -std=c++14

## Laborator 3 — Constructori și operatori

Pentru structurile de date ale jocului au fost definiți constructori (implicit, cu
parametri) și operatori (comparare `==` / `!=`, intrare/ieșire `>>` / `<<`).
Pentru redare a fost definită clasa de bază abstractă `Drawable`, din care moștenește
clasa `Painter`.

## Laborator 4 — Utilizarea bibliotecii standard C++

La acest laborator jocul a fost rescris pentru a folosi biblioteca standard C++:

- **Containere STL**: tabla folosește `std::array<std::array<Cell,3>,3>` în loc de un
  tablou C brut.
- **Smart pointers**: jucătorii sunt ținuți prin `std::unique_ptr<Player>`, fără
  alocare manuală de memorie.
- **std::string**: mesajele afișate folosesc `std::string` în loc de `char*`.
- **Fluxuri I/O**: citirea și afișarea se fac prin `std::cin` / `std::cout` și
  operatorii `>>` / `<<`.
- **Algoritmi STL**: `std::fill`, `std::all_of`, `std::none_of` pentru operațiile pe
  tablă.

De asemenea, a fost completată logica jocului:

- interfața `Player` (clasă abstractă) cu `HumanPlayer` (joacă de la tastatură) și
  `ComputerPlayer` (joacă singur: câștigă dacă poate, altfel blochează adversarul);
- starea de remiză (`Draw`) prin enumerarea `GameResult`;
- bucla principală de joc completă în `GameEngine::Run()`, cu alegerea modului de joc
  (unul sau doi jucători) la pornire.
