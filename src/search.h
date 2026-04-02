#pragma once

#include <array>
#include <cassert>

#include "bitboard.h"
#include "evaluate.h"
#include "movegen.h"
#include "position.h"
#include "tt.h"
#include "types.h"

namespace ConnectFour {
extern TranspositionTable TT;
class Search {
public:
  Search() = default;
  Bitboard solve(const Position &pos, int depth);
  int16_t negamax_recursive(Position &pos, int16_t alpha, int16_t beta,
                            uint8_t depth);

private:
};

} // namespace ConnectFour
