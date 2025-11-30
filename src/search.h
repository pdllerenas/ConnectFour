#pragma once

#include <array>
#include <cassert>

#include "bitboard.h"
#include "position.h"
#include "types.h"
#include "evaluate.h"
#include "movegen.h"

namespace ConnectFour {
class Search {
public:
	Search() {
		nodeCount = 0;
	}
  Bitboard solve(const Position &pos, int depth);

private:
  Bitboard negamax(const Position &pos, int16_t alpha, int16_t beta, uint8_t max_depth);
	size_t nodeCount;

};

} // namespace ConnectFour
