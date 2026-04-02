#include <iostream>
#include <string>

#include "position.h"

constexpr std::string_view PieceToChar(" OX");

namespace ConnectFour {
std::ostream &operator<<(std::ostream &os, const Position &pos) {
  os << "\n+---+---+---+---+---+---+---+\n";

  for (Rank r = RANK_6; r >= RANK_1; --r) {
    for (File f = FILE_A; f <= FILE_G; ++f) {
      os << "| " << PieceToChar[pos.piece_on(make_square(f, r))] << " ";
    }
    os << "| " + std::to_string(1 + r) + "\n+---+---+---+---+---+---+---+\n";
  }
  os << "  a   b   c   d   e   f   g\n";
  return os;
}


bool Position::is_valid(File F) const {
  return (bothPieces & Rank6BB & file_bb(F)) == 0;
}

void Position::play(Bitboard move) {
  currentPieces ^= bothPieces;
  bothPieces |= move;
  ply++;
}

void Position::play(File f) {
  play((bothPieces + (Rank1BB & file_bb(f))) & file_bb(f));
}

}; // namespace ConnectFour
