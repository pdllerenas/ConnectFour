#include <iostream>
#include <string>

#include "position.h"

constexpr std::string_view PieceToChar(" BR");

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

void Position::do_move(File F) {
  Square sq = lsb(~bothPieces & file_bb(F));
  if (sideToMove == BLUE) {
    bluePieces |= sq;
  } else {
    redPieces |= sq;
  }
  bothPieces |= sq;
  sideToMove = ~sideToMove;
}

Value Position::is_terminal() const {
  // check if blue has won horizontally
  if (bluePieces & (bluePieces >> 1) & (bluePieces >> 2) & (bluePieces >> 3)) {
		return BLUE_WIN;
  }
  // check if red has won horizontally
  if (redPieces & (redPieces >> 1) & (redPieces >> 2) & (redPieces >> 3)) {
		return RED_WIN;
  }

  // check if blue has won vertically
  if (bluePieces & (bluePieces >> 8) & (bluePieces >> 16) & (bluePieces >> 24)) {
		return BLUE_WIN;
  }
  // check if red has won vertically
  if (redPieces & (redPieces >> 8) & (redPieces >> 16) & (redPieces >> 24)) {
		return RED_WIN;
  }

  // check if blue has won diagonally ( / )
  if (bluePieces & (bluePieces >> 6) & (bluePieces >> 12) & (bluePieces >> 18)) {
		return BLUE_WIN;
  }
  // check if red has won diagonally ( / )
  if (redPieces & (redPieces >> 6) & (redPieces >> 12) & (redPieces >> 18)) {
		return RED_WIN;
  }

  // check if blue has won diagonally ( \ )
  if (bluePieces & (bluePieces >> 9) & (bluePieces >> 18) & (bluePieces >> 27)) {
		return BLUE_WIN;
  }
  // check if red has won diagonally ( \ )
  if (redPieces & (redPieces >> 9) & (redPieces >> 18) & (redPieces >> 27)) {
		return RED_WIN;
  }
	return DRAW;
}

}; // namespace ConnectFour
