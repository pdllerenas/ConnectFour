#pragma once

#include <cassert>
#include <string>

#include "types.h"

namespace ConnectFour {
namespace Bitboards {

std::string pretty(Bitboard b);

} // namespace Bitboards

/*
 * A bitboard consists of 64 bits. We will be using 7x7 of them to represent
 * our Connect Four board:
 *
 * .  .  .  .  .  .  .
 * 5 12 19 26 33 40 47
 * 4 11 18 25 32 39 46
 * 3 10 17 24 31 38 45
 * 2  9 16 23 30 37 44
 * 1  8 15 22 29 36 43
 * 0  7 14 21 28 35 42
 *
 * where the top . are sentinel values, meaning they are there to delimit the
 * board.
 *
 */

constexpr Bitboard FileABB = 0x7F;
constexpr Bitboard FileBBB = FileABB << (7 * 1);
constexpr Bitboard FileCBB = FileABB << (7 * 2);
constexpr Bitboard FileDBB = FileABB << (7 * 3);
constexpr Bitboard FileEBB = FileABB << (7 * 4);
constexpr Bitboard FileFBB = FileABB << (7 * 5);
constexpr Bitboard FileGBB = FileABB << (7 * 6);

constexpr Bitboard FilesBB[7] = {
    FileABB, FileBBB, FileCBB, FileDBB, FileEBB, FileFBB, FileGBB,
};

constexpr Bitboard Rank1BB = (1ULL << 0) | (1ULL << 7) | (1ULL << 14) |
                             (1ULL << 21) | (1ULL << 28) | (1ULL << 35) |
                             (1ULL << 42);
constexpr Bitboard Rank2BB = Rank1BB << 1;
constexpr Bitboard Rank3BB = Rank1BB << 2;
constexpr Bitboard Rank4BB = Rank1BB << 3;
constexpr Bitboard Rank5BB = Rank1BB << 4;
constexpr Bitboard Rank6BB = Rank1BB << 5;

// mask of all available playable bits
constexpr Bitboard FULL_BOARD = Rank1BB * ((1ULL << 6) - 1);

constexpr Bitboard square_bb(Square s) { return (1ULL << s); }

constexpr Bitboard operator&(Bitboard b, Square s) { return b & square_bb(s); }
constexpr Bitboard operator|(Bitboard b, Square s) { return b | square_bb(s); }
constexpr Bitboard operator^(Bitboard b, Square s) { return b ^ square_bb(s); }
constexpr Bitboard operator|=(Bitboard &b, Square s) {
  return b |= square_bb(s);
}
constexpr Bitboard operator^=(Bitboard &b, Square s) {
  return b ^= square_bb(s);
}

constexpr Bitboard operator&(Square s, Bitboard b) { return b & s; }
constexpr Bitboard operator|(Square s, Bitboard b) { return b | s; }
constexpr Bitboard operator^(Square s, Bitboard b) { return b ^ s; }

constexpr Bitboard operator|(Square s1, Square s2) {
  return square_bb(s1) | s2;
}

constexpr Bitboard rank_bb(Rank r) { return Rank1BB << r; }

constexpr Bitboard file_bb(File f) { return FileABB << (7 * f); }

// counts the number of non-zero bits in a bitboard
inline int popcount(Bitboard b) { return __builtin_popcountll(b); }

// returns the least significant bit of a bitboard
inline int lsb(Bitboard b) { return __builtin_ctzll(b); }

} // namespace ConnectFour
