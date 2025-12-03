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
      p.play(f);
    } else {
      std::cout << "Cannot play this column." << std::endl;
      continue;
    }

    // Bot movement
    best_move = s.solve(p, 3);
    if (best_move == Move::NULL_MOVE) {
      std::cout << "You win!" << std::endl;
      return 0;
    }
    if (MoveGen::possible(p) == 0) {
      std::cout << "Draw" << std::endl;
      return 0;
    }
    if (Eval::is_winning_move(p, best_move)) {
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
