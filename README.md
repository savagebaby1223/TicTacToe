# TicTacToe

## Despre proiect

Acest proiect este o implementare a jocului clasic X și 0 (Tic-tac-toe), scrisă în
limbajul C++. Doi jucători se înfruntă pe o tablă de 3×3 căsuțe, punând pe rând
simbolul lor (X sau O). Câștigă cel care reușește primul să alinieze trei simboluri
identice pe un rând, o coloană sau o diagonală.

## Cum se joacă

1. Tabla are 9 căsuțe, dispuse pe 3 rânduri și 3 coloane, toate goale la început.
2. Cei doi jucători mută pe rând: unul joacă cu X, celălalt cu O.
3. La rândul său, un jucător alege o căsuță liberă și își pune simbolul acolo.
4. O căsuță deja ocupată nu poate fi aleasă din nou.
5. Partida este câștigată de jucătorul care aliniază trei simboluri identice pe
   orizontală, verticală sau diagonală.
6. Dacă toate căsuțele sunt ocupate și nimeni nu a aliniat trei simboluri, partida
   se termină la egalitate (remiză).

## Tipurile de date folosite

- **Point** (`point.hpp`) — o structură care reține o poziție pe tablă, prin rândul
  (`row`) și coloana (`col`) sale.
- **Cell** (`cell.hpp`) — o enumerare ce descrie starea unei căsuțe: goală (Empty),
  ocupată cu X sau ocupată cu O.
- **Player** (`player.hpp`) — o clasă ce reprezintă un jucător, caracterizat prin
  simbolul cu care joacă (X sau O).
- **Board** (`board.hpp`) — clasa tablei de joc; păstrează conținutul celor 9 căsuțe
  într-o matrice 3×3 și oferă operații de plasare a simbolurilor, golire și verificare
  a stării tablei.
- **GameEngine** (`game_engine.hpp`) — motorul jocului; reunește tabla și jucătorii,
  ține evidența jucătorului aflat la rând și aplică regulile (mutări valide, verificarea
  câștigătorului, schimbarea rândului).
- **Painter** (`painter.hpp`) — componenta de afișare, care desenează tabla pe ecran
  și afișează mesajele către jucători.
- **Listener** (`listener.hpp`) — componenta care preia intrarea de la jucător: căsuța
  aleasă pentru mutare și eventuala intenție de a părăsi jocul.