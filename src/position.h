#pragma once

#include <array>
#include <cassert>

#include "bitboard.h"
#include "types.h"

namespace ConnectFour {
class Position {
public:
  Position() = default;
  Position(const Position &) = delete;
  Position &operator=(const Position &) = delete;

  void do_move(File f);

  Piece piece_on(Square s) const;
	Piece side_to_move() const;

	Value is_terminal() const;

private:
  std::array<Piece, SQUARE_NB> board;
  Bitboard bluePieces = 0ULL;
  Bitboard redPieces = 0ULL;
  Bitboard bothPieces = 0ULL;
  Piece sideToMove = BLUE;
};

std::ostream &operator<<(std::ostream &os, const Position &pos);

inline Piece Position::piece_on(Square s) const {
  assert(is_ok(s));
  if (bluePieces & square_bb(s)) {
    return BLUE;
  } else if (redPieces & square_bb(s)) {
		return RED;
  } else {
		return NO_PIECE;
	}
}

inline Piece Position::side_to_move() const {
	return sideToMove;
}

} // namespace ConnectFour
