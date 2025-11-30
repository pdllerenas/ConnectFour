#pragma once

#include "position.h"
#include "types.h"

namespace ConnectFour {
namespace Eval {
bool is_winning_move(const Position &pos, File f);
bool is_winning_move(const Position &pos, Bitboard bb);
bool can_win_next(const Position &pos);
int move_score(const Position &pos, Bitboard move);
Bitboard generate_non_losing_moves(const Position &pos);
int position_score(const Position &pos);
Bitboard winning_position(const Position &pos);
} // namespace Eval

} // namespace ConnectFour
