#pragma once

#include "bitboard.h"
#include "position.h"

namespace ConnectFour {
namespace MoveGen {
Bitboard possible(const Position &pos);
Bitboard generate_non_losing_moves(const Position &pos);

constexpr int file_order[7] = {3, 4, 2, 5, 1, 6, 0};

} // namespace MoveGen
} // namespace ConnectFour
