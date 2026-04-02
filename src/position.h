#pragma once

#include <array>
#include <cassert>

#include "bitboard.h"
#include "types.h"

namespace ConnectFour {
class Position {
public:
  Position() {
    currentPieces = 0ULL;
    bothPieces = 0ULL;
    ply = 0;
  }

  uint64_t key() const {
    // We use a pseudo-random constant (the golden ratio) to mix the two
    // bitboards. This guarantees no collisions for any valid Connect Four
    // position.
    uint64_t hashing_constant = 0x9e3779b97f4a7c15ULL;

    // Replace these with your actual internal Bitboard variables
    return currentPieces ^ (bothPieces + hashing_constant);
  }
  Piece piece_on(Square s) const;
  bool is_valid(File f) const;
  void play(File f);
  void play(Bitboard move);
  Bitboard get_current_mask() const;
  Bitboard get_full_mask() const;
  uint8_t get_ply() const;

private:
  Bitboard currentPieces;
  Bitboard bothPieces;
  uint8_t ply;

  Bitboard winning_move_mask(Bitboard position, Bitboard mask) const;
};

std::ostream &operator<<(std::ostream &os, const Position &pos);

inline Piece Position::piece_on(Square s) const {
  if (bothPieces & square_bb(s)) {
    if (ply % 2) {
      return currentPieces & square_bb(s) ? RED : BLUE;
    } else {
      return currentPieces & square_bb(s) ? BLUE : RED;
    }
  } else {
    return NO_PIECE;
  }
}

inline Bitboard Position::get_full_mask() const { return bothPieces; }

inline Bitboard Position::get_current_mask() const { return currentPieces; }

inline uint8_t Position::get_ply() const { return ply; }
} // namespace ConnectFour
