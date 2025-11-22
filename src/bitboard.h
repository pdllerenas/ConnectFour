#pragma once

#include <cassert>
#include <string>

#include "types.h"

namespace ConnectFour {
namespace Bitboards {

std::string pretty(Bitboard b);

} // namespace Bitboards

constexpr Bitboard FileABB = 0x10101010101ULL;
constexpr Bitboard FileBBB = FileABB << 1;
constexpr Bitboard FileCBB = FileABB << 2;
constexpr Bitboard FileDBB = FileABB << 3;
constexpr Bitboard FileEBB = FileABB << 4;
constexpr Bitboard FileFBB = FileABB << 5;
constexpr Bitboard FileGBB = FileABB << 6;

constexpr Bitboard Rank1BB = 0xFF;
constexpr Bitboard Rank2BB = Rank1BB << (8 * 1);
constexpr Bitboard Rank3BB = Rank1BB << (8 * 2);
constexpr Bitboard Rank4BB = Rank1BB << (8 * 3);
constexpr Bitboard Rank5BB = Rank1BB << (8 * 4);
constexpr Bitboard Rank6BB = Rank1BB << (8 * 5);

constexpr Bitboard square_bb(Square s) {
  assert(is_ok(s));
  return (1ULL << s);
}

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

constexpr Bitboard rank_bb(Rank r) { return Rank1BB << (8 * r); }
constexpr Bitboard rank_bb(Square s) { return rank_bb(rank_of(s)); }

constexpr Bitboard file_bb(File f) { return FileABB << f; }
constexpr Bitboard file_bb(Square s) { return file_bb(file_of(s)); }

inline Square lsb(Bitboard b) { return Square(__builtin_ctzll(b)); }

} // namespace ConnectFour
