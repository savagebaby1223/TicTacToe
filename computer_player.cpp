#include "computer_player.hpp"
#include "board.hpp"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

ComputerPlayer::ComputerPlayer(Cell symbol) : Player(symbol) {}

// toate casutele libere de pe tabla (container STL std::vector)
static std::vector<Point> FreeCells(const Board& board) {
    std::vector<Point> cells;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board.GetCell({ r, c }) == Cell::Empty)
                cells.push_back({ r, c });
    return cells;
}

int ComputerPlayer::Minimax(const Board& board, bool myTurn, int depth) const {
    Cell opponent = (_symbol == Cell::X) ? Cell::O : Cell::X;

    // stari finale: castig rapid = scor mai mare, pierdere tarzie = scor mai mic
    Cell winner = board.GetWinner();
    if (winner == _symbol)  return 10 - depth;
    if (winner == opponent) return depth - 10;
    if (board.IsFull())     return 0;

    // la randul meu caut scorul maxim, la randul adversarului scorul minim
    int best = myTurn ? -100 : 100;
    for (const Point& p : FreeCells(board)) {
        Board next = board;   // simulez mutarea pe o copie a tablei
        next.PlaceSymbol(p, myTurn ? _symbol : opponent);
        int score = Minimax(next, !myTurn, depth + 1);
        best = myTurn ? std::max(best, score) : std::min(best, score);
    }
    return best;
}

Point ComputerPlayer::GetMove(const Board& board) const {
    std::cout << "Calculatorul (" << (_symbol == Cell::X ? 'X' : 'O') << ") alege mutarea...\n";

    std::vector<Point> moves = FreeCells(board);
    if (moves.empty()) return { -1, -1 };

    // scorul fiecarei mutari posibile
    std::vector<int> scores;
    for (const Point& p : moves) {
        Board next = board;
        next.PlaceSymbol(p, _symbol);
        scores.push_back(Minimax(next, false, 1));
    }

    // algoritm STL std::max_element: cel mai bun scor
    int bestScore = *std::max_element(scores.begin(), scores.end());

    // pastrez toate mutarile la fel de bune
    std::vector<Point> bestMoves;
    for (size_t i = 0; i < moves.size(); i++)
        if (scores[i] == bestScore)
            bestMoves.push_back(moves[i]);

    // aleg una la intamplare, ca partidele sa nu fie mereu identice
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> pick(0, bestMoves.size() - 1);
    return bestMoves[pick(rng)];
}
