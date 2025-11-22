#pragma once

#include <cstdint>

using Bitboard = uint64_t;

enum File : int8_t {
  FILE_A,
  FILE_B,
  FILE_C,
  FILE_D,
  FILE_E,
  FILE_F,
  FILE_G,
  FILE_H,
  FILE_NB
};

enum Rank : int8_t {
  RANK_1,
  RANK_2,
  RANK_3,
  RANK_4,
  RANK_5,
  RANK_6,
  RANK_7,
  RANK_8,
  RANK_NB
};

enum Piece : int8_t { NO_PIECE, BLUE, RED };

// clang-format off
enum Square : int8_t {
    SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
    SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
    SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
    SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
    SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
    SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
    SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
    SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
    SQ_NONE,

    SQUARE_ZERO = 0,
    SQUARE_NB   = 64
};
// clang-format on

enum Value : int8_t {
	BLUE_WIN = -1,
	DRAW = 0,
	RED_WIN = 1,
};

constexpr Rank &operator++(Rank &d) { return d = Rank(int(d) + 1); }
constexpr Rank &operator--(Rank &d) { return d = Rank(int(d) - 1); }

constexpr File &operator++(File &d) { return d = File(int(d) + 1); }
constexpr File &operator--(File &d) { return d = File(int(d) - 1); }

// only acceptable squares are in the 6x7 grid
constexpr bool is_ok(Square s) { return s >= SQ_A1 && s <= SQ_G6; }

constexpr Square make_square(File f, Rank r) { return Square((r << 3) + f); }

// todo: understand & 7
constexpr File file_of(Square s) { return File(s & 7); }
constexpr Rank rank_of(Square s) { return Rank(s >> 3); }

constexpr Piece operator~(Piece p) {
	return Piece(p ^ 3);
}
