#include <iostream>

#include "bitboard.h"
#include "evaluate.h"
#include "movegen.h"
#include "position.h"
#include "search.h"

using namespace ConnectFour;

int main() {
  Position p;
  Search s;

  Bitboard best_move;
  char file;

  unsigned int depth = 0; // TODO: fix even depth
  while (depth > 10 || depth < 1) {
    std::cout << "Enter a difficulty: 1 - 10" << std::endl;
    std::cin >> depth;
  }
  depth *= 2;
  depth++;
  std::cout << p << std::endl;

  while (true) {
    if (MoveGen::possible(p) == 0) {
      std::cout << "Draw" << std::endl;
    }
    std::cout << "Enter a move (column A-G)." << std::endl;
    std::cin >> file;
    int file_ch = std::tolower(file) - 'a';
    if (file_ch < 0 || file_ch > 6) {
      std::cout << "Invalid column." << std::endl;
      continue;
    }
    File f = File(file_ch);
    if (p.is_valid(f)) {
      if (Eval::is_winning_move(p, f)) {
        p.play(f);
        std::cout << p << std::endl;
        std::cout << "You win!" << std::endl;
        return 0;
      }
      p.play(f);
    } else {
      std::cout << "Cannot play this column." << std::endl;
      continue;
    }

    // Bot movement
    best_move = s.solve(p, depth);
    if (best_move == Move::NULL_MOVE) {
      p.play(1ULL << lsb(MoveGen::possible(p)));
      std::cout << p << std::endl;
      char bot_file = 'A' + (lsb(MoveGen::possible(p)) / 7);
      std::cout << "Bot played: " << bot_file << 1 + (lsb(MoveGen::possible(p)) % 7)
                << std::endl;
      continue;
    } else if (MoveGen::possible(p) == 0) {
      std::cout << "Draw" << std::endl;
      return 0;
    } else if (Eval::is_winning_move(p, best_move)) {
      p.play(best_move);
      std::cout << p << std::endl;
      std::cout << "You lose!" << std::endl;
      return 0;
    }

    p.play(best_move);

    // Updated board
    std::cout << p << std::endl;
    char bot_file = 'A' + (lsb(best_move) / 7);
    std::cout << "Bot played: " << bot_file << 1 + (lsb(best_move) % 7)
              << std::endl;
  }
  return 0;
}
