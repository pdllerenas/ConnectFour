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
  FILE_NB
};

enum Rank : int8_t { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_NB };

constexpr Rank &operator++(Rank &d) { return d = Rank(int(d) + 1); }
constexpr Rank &operator--(Rank &d) { return d = Rank(int(d) - 1); }

constexpr File &operator++(File &d) { return d = File(int(d) + 1); }
constexpr File &operator--(File &d) { return d = File(int(d) - 1); }
