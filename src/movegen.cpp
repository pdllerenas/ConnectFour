#include <iostream>

#include "movegen.h"

namespace ConnectFour {
namespace MoveGen {

Bitboard possible(const Position &pos) {
  return (pos.get_full_mask() + Rank1BB) & FULL_BOARD;
}

Bitboard generate_non_losing_moves(const Position &pos) {
  Bitboard possible_mask = possible(pos);
	return possible_mask;
}

} // namespace MoveGen

} // namespace ConnectFour
