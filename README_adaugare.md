## Laborator 4 — Utilizarea bibliotecii standard C++

La acest laborator jocul a fost rescris pentru a folosi biblioteca standard C++:

- **Containere STL**: tabla folosește `std::array<std::array<Cell,3>,3>` în loc de un array C brut.
- **Smart pointers**: jucătorii sunt ținuți prin `std::unique_ptr<Player>`, fără alocare manuală de memorie.
- **std::string**: mesajele afișate folosesc `std::string` în loc de `char*`.
- **Fluxuri I/O**: citirea și afișarea se fac prin `std::cin` / `std::cout` și operatorii `>>` / `<<`.
- **Algoritmi STL**: `std::fill`, `std::all_of`, `std::none_of` pentru operațiile pe tablă.

De asemenea, a fost completată logica jocului:
- interfața `Player` (clasă abstractă) cu `HumanPlayer` (joacă de la tastatură) și `ComputerPlayer` (joacă singur: câștigă dacă poate, altfel blochează adversarul);
- starea de remiză (`Draw`) prin enumerarea `GameResult`;
- bucla principală de joc completă în `GameEngine::Run()`.
