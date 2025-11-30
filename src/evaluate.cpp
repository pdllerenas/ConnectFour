#include "evaluate.h"

namespace ConnectFour {
namespace Eval {
static Bitboard winning_move_mask(Bitboard position, Bitboard mask) {
  // vertical
  Bitboard r =
      (position << NORTH) & (position << 2 * NORTH) & (position << 3 * NORTH);

  /* horizontal */
  Bitboard p = (position << EAST) & (position << 2 * EAST);
  // case ooo( ) (right-most stone space)
  r |= p & (position << 3 * EAST);
  // case oo( )o
  r |= p & (position >> EAST);

  p = (position >> EAST) & (position >> 2 * EAST);
  // case o( )oo
  r |= p & (position << EAST);
  // case ( )ooo (left-most stone space)
  r |= p & (position >> 3 * EAST);

  /* diagonal (/) */
  p = (position << -NORTH_WEST) & (position << 2 * -NORTH_WEST);

  // case
  // 	  ( )
  //	 o
  //  o
  // o
  r |= p & (position << 3 * -NORTH_WEST);

  // case
  // 	   o
  //	 ( )
  //  o
  // o
  r |= p & (position >> -NORTH_WEST);

  p = (position >> -NORTH_WEST) & (position >> 2 * -NORTH_WEST);

  // case
  // 	  o
  //	 o
  //  o
  //( )
  r |= p & (position << -NORTH_WEST);

  // case
  // 	  o
  //	 o
  // ( )
  // o
  r |= p & (position >> 3 * -NORTH_WEST);

  /* diagonal (\) */
  p = (position << NORTH_EAST) & (position << 2 * NORTH_EAST);
  r |= p & (position << 3 * NORTH_EAST);
  r |= p & (position >> NORTH_EAST);

  p = (position >> NORTH_EAST) & (position >> 2 * NORTH_EAST);
  r |= p & (position << NORTH_EAST);
  r |= p & (position >> 3 * NORTH_EAST);

  // only consider bits in r which are not already occupied
  return r & (FULL_BOARD ^ mask);
}

Bitboard winning_position(const Position &pos) {
  return winning_move_mask(pos.get_current_mask(), pos.get_full_mask());
}

Bitboard opponent_winning_position(const Position &pos) {
  return winning_move_mask(pos.get_current_mask() ^ pos.get_full_mask(),
                           pos.get_full_mask());
}

Bitboard possible(const Position &pos) {
  return (pos.get_full_mask() + Rank1BB) & FULL_BOARD;
}

Bitboard generate_non_losing_moves(const Position &pos) {
  Bitboard possible_mask = possible(pos);
  Bitboard opponent_win = opponent_winning_position(pos);
  Bitboard forced_moves = possible_mask & opponent_win;
  if (forced_moves) {
    if (forced_moves & (forced_moves - 1)) {
      return 0;
    } else {
      possible_mask = forced_moves;
    }
  }
  return possible_mask & ~(opponent_win >> 1);
}

bool is_winning_move(const Position &pos, File f) {
  return winning_position(pos) & possible(pos) & file_bb(f);
}

bool is_winning_move(const Position &pos, Bitboard bb) {
  return winning_position(pos) & possible(pos) & bb;
}

int move_score(const Position &pos, Bitboard move) {
  return popcount(
      winning_move_mask(pos.get_current_mask() | move, pos.get_full_mask()));
}

bool can_win_next(const Position &pos) {
  return winning_position(pos) & possible(pos);
}

int position_score(const Position &pos) {
  if (can_win_next(pos)) {
    return 32000;
  }
  int own_threes =
      popcount(winning_move_mask(pos.get_current_mask(), pos.get_full_mask()));
  int opp_threes = popcount(winning_move_mask(
      pos.get_current_mask() ^ pos.get_full_mask(), pos.get_full_mask()));

  int score = 1000 * (own_threes - opp_threes);

  int center =
      10 * (popcount(pos.get_current_mask() & FileDBB) -
            popcount((pos.get_current_mask() ^ pos.get_full_mask()) & FileDBB));

  return score + center;
}

} // namespace Eval

} // namespace ConnectFour
