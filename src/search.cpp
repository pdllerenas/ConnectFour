#include "search.h"

namespace ConnectFour {

TranspositionTable TT(64);

int16_t Search::negamax_recursive(Position &pos, int16_t alpha, int16_t beta,
                                  uint8_t depth) {
  if (Eval::can_win_next(pos)) {
    return 32000 - depth; // Positive score relative to the current player
  }

  if (depth == 0) {
    return Eval::position_score(pos);
  }

  uint64_t pos_key =
      pos.key();
  TTEntry tt_entry;
  int16_t original_alpha =
      alpha; // Remember original alpha to determine TT flag later
  Bitboard tt_best_move = Move::NULL_MOVE;

  if (TT.probe(pos_key, tt_entry)) {
    tt_best_move = tt_entry.best_move;
    if (tt_entry.depth >= depth) {
      if (tt_entry.flag == TT_EXACT) {
        return tt_entry.score;
      } else if (tt_entry.flag == TT_LOWERBOUND) {
        alpha = std::max(alpha, tt_entry.score);
      } else if (tt_entry.flag == TT_UPPERBOUND) {
        beta = std::min(beta, tt_entry.score);
      }

      if (alpha >= beta) {
        return tt_entry.score; // Cutoff
      }
    }
  }

  Bitboard moves = MoveGen::possible(pos);
  if (!moves)
    return 0;

  Bitboard best_move = Move::NULL_MOVE;
  int16_t best_score = -32001;

  if (tt_best_move != Move::NULL_MOVE) {
    Position next_pos = pos;
    next_pos.play(tt_best_move);
    int16_t score = -negamax_recursive(next_pos, -beta, -alpha, depth - 1);

    if (score > best_score) {
      best_score = score;
      best_move = tt_best_move;
    }
    alpha = std::max(alpha, score);
    // If the TT move was good enough, we may cut off
    if (alpha >= beta) {
      TT.store(pos_key, best_score, depth, TT_LOWERBOUND, best_move);
      return best_score;
    }
  }

  for (int i = 0; i < 7; ++i) {
    int file = MoveGen::file_order[i];
    Bitboard move = FilesBB[file] & moves;
    if (!move || move == tt_best_move)
      continue;

    Position next_pos = pos;
    next_pos.play(move);

    int16_t score = -negamax_recursive(next_pos, -beta, -alpha, depth - 1);

    if (score > best_score) {
      best_score = score;
      best_move = move;
    }

    alpha = std::max(alpha, score);
    if (alpha >= beta) {
      break; // Alpha-beta cutoff
    }
  }

  TTFlag flag = TT_EXACT;
  if (best_score <= original_alpha) {
    flag = TT_UPPERBOUND; // Failed low
  } else if (best_score >= beta) {
    flag = TT_LOWERBOUND; // Failed high
  }

  TT.store(pos_key, best_score, depth, flag, best_move);

  return best_score;
}

Bitboard Search::solve(const Position &pos, int target_depth) {
  if (Eval::can_win_next(pos)) {
    return 1ULL << lsb(Eval::winning_position(pos) & MoveGen::possible(pos));
  }

  Bitboard absolute_best_move = Move::NULL_MOVE;

  for (int current_depth = 1; current_depth <= target_depth; ++current_depth) {
    int16_t alpha = -32001;
    int16_t beta = 32001;
    Bitboard best_root_move = Move::NULL_MOVE;
    int16_t best_score = -32001;

    Bitboard moves = MoveGen::possible(pos);

    if (absolute_best_move != Move::NULL_MOVE) {
      Position next_pos = pos;
      next_pos.play(absolute_best_move);
      int16_t score =
          -negamax_recursive(next_pos, -beta, -alpha, current_depth - 1);

      if (score > best_score) {
        best_score = score;
        best_root_move = absolute_best_move;
      }
      alpha = std::max(alpha, score);
    }

    for (int i = 0; i < 7; ++i) {
      int file = MoveGen::file_order[i];
      Bitboard move = FilesBB[file] & moves;

      if (!move || move == absolute_best_move)
        continue;

      Position next_pos = pos;
      next_pos.play(move);

      int16_t score =
          -negamax_recursive(next_pos, -beta, -alpha, current_depth - 1);

      if (score > best_score) {
        best_score = score;
        best_root_move = move;
      }
      alpha = std::max(alpha, score);
    }

    absolute_best_move = best_root_move;

    if (best_score > 30000 || best_score < -30000) {
      break;
    }
  }

  return absolute_best_move;
}
} // namespace ConnectFour
