#include <stack>

#include "search.h"

namespace ConnectFour {

// maybe depth is not needed, can use pos.ply, best_move logic can possibly be
// moved to a wrapper function (solve)
struct C4Node {
  Position pos;
  int16_t alpha, beta;
  uint8_t depth;
  uint8_t move_index;
  Bitboard moves;
  uint8_t move_count;
  int16_t best_score;
  Bitboard best_move;

  C4Node(Position p, int16_t alpha, int16_t beta, uint8_t depth,
         uint8_t move_index, Bitboard moves, uint8_t move_count,
         int16_t best_score, Bitboard best_move)
      : pos(p), alpha(alpha), beta(beta), depth(depth), move_index(move_index),
        moves(moves), move_count(move_count), best_score(best_score),
        best_move(best_move) {}
};

Bitboard Search::negamax(const Position &p, int16_t alpha, int16_t beta,
                         uint8_t max_depth) {
  std::stack<C4Node> s;

  Bitboard possible = Eval::generate_non_losing_moves(p);

  if (possible == 0) {
    return Move::NULL_MOVE;
  }

  // root node
  C4Node node(p, alpha, beta, 0, 0, possible,
              static_cast<uint8_t>(popcount(possible)), -32000, 0ULL);
  s.push(node);

  while (!s.empty()) {
    C4Node &curr = s.top();

    if (curr.depth == max_depth || curr.moves == 0 || curr.depth == 42) {
      int16_t score;
      if (curr.moves == 0) {
        score = -32000;
      } else if (curr.depth == 42) {
        score = 0;
      } else {
        score = Eval::position_score(curr.pos);
      }

      s.pop();

      if (s.empty())
        return Move::NULL_MOVE;

      C4Node &parent = s.top();
      score = -score;

      int prev_file = MoveGen::file_order[parent.move_index - 1];
      Bitboard move_evaluated = FilesBB[prev_file] & parent.moves;

      if (score > parent.best_score) {
        parent.best_score = score;
        parent.best_move = move_evaluated;
      }

      if (score > parent.alpha) {
        parent.alpha = score;
      }

      if (parent.alpha >= parent.beta) {
        parent.move_index = 7; // Prune remaining siblings
      }
      continue;
    }

    if (curr.move_index >= 7) {
      int16_t score = curr.best_score;
      Bitboard best_move_found = curr.best_move;

      s.pop();

      if (s.empty())
        return best_move_found;

      C4Node &parent = s.top();
      score = -score;

      int prev_file = MoveGen::file_order[parent.move_index - 1];
      Bitboard move_evaluated = FilesBB[prev_file] & parent.moves;

      if (score > parent.best_score) {
        parent.best_score = score;
        parent.best_move = move_evaluated;
      }

      if (score > parent.alpha) {
        parent.alpha = score;
      }

      if (parent.alpha >= parent.beta) {
        parent.move_index = 7; // Prune remaining siblings
      }
      continue;
    }

    int file = MoveGen::file_order[curr.move_index++];
    Bitboard move = FilesBB[file] & curr.moves;

    if (!move)
      continue;

    Position next(curr.pos);
    next.play(move);
    Bitboard next_possible = Eval::generate_non_losing_moves(next);

    C4Node child(next, -curr.beta, -curr.alpha, curr.depth + 1, 0,
                 next_possible, static_cast<uint8_t>(popcount(next_possible)),
                 -32000, 0ULL);
    s.push(child);
  }
  return Move::NULL_MOVE;
}

Bitboard Search::solve(const Position &pos, int depth) {
  // If a winning move is available, dont go into negamax.
  if (Eval::can_win_next(pos)) {
    return 1ULL << lsb(Eval::winning_position(pos) & MoveGen::possible(pos));
  }
  return negamax(pos, -32001, 32001, depth);
}
} // namespace ConnectFour
