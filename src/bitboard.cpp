#include <iostream>

#include "bitboard.h"

namespace ConnectFour {
std::string Bitboards::pretty(Bitboard b) {
  std::string s = "+---+---+---+---+---+---+---+\n";

  for (Rank r = RANK_6; r >= RANK_1; --r) {
    for (File f = FILE_A; f <= FILE_G; ++f) {
      s += "|   ";
    }
    s += "| " + std::to_string(1 + r) + "\n+---+---+---+---+---+---+---+\n";
  }
	s += "  a   b   c   d   e   f   g\n";
  return s;
}

} // namespace ConnectFour
