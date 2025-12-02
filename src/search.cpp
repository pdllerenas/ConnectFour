#include <iostream>
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

  // root node
  C4Node node(p, alpha, beta, 0, 0, possible,
              static_cast<uint8_t>(popcount(possible)), -32000, 0ULL);
  s.push(node);

  while (!s.empty()) {
    // reference to most recently added node
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

      // origin move so we can return it when the best score is found
      Bitboard root_move = curr.best_move;
      s.pop();

      // if we are done searching the tree, return best move
      if (s.empty())
        return root_move;

      // reference to parent of recently deleted node
      C4Node &parent = s.top();

      // reverse sign of score, as we have popped the previous move and are now
      // in the perspective of the other player, and we want to maximize -score
      score = -score;

      // if a better score is found, update alpha
      if (score > parent.alpha) {
        parent.alpha = score;

        // if parent is root node, update best move on parent node
        if (parent.depth == 0) {
          parent.best_move = root_move;
        }
      }

      // alpha-beta cutoff
      if (parent.alpha >= parent.beta) {
        s.pop();
        // if at root, return best move
        if (s.empty())
          return parent.best_move;
        // if not, force quit current branch search
        s.top().move_index = 7;
      }
      continue;
    }

    // check if all moves have been explored
    if (curr.move_index >= 7) {
      int16_t score = curr.alpha;
      Bitboard best_move = curr.best_move;
      s.pop();

      // if we are at root, return best move
      if (s.empty())
        return best_move;

      C4Node &parent = s.top();
      score = -score;

      // if better score is found, update parent alpha
      if (score > parent.alpha) {
        parent.alpha = score;

        // if parent is root, update best move
        if (parent.depth == 0) {
          parent.best_move = best_move;
        }
      }

      // alpha-beta cutoff
      if (parent.alpha >= parent.beta) {
        s.pop();
        if (s.empty())
          return parent.best_move;
        s.top().move_index = 7;
      }
      continue;
    }

    // if there are still moves left and no evaluation is needed yet,
    // explore moves in order (center first - borders last)
    int file = MoveGen::file_order[curr.move_index++];
    Bitboard move = FilesBB[file] & curr.moves; // get move from bitboard mask

    // if file does not contain a non-losing move, skip
    if (!move)
      continue;

    // setup of next position object
    Position next(curr.pos);
    next.play(move);
    Bitboard next_possible = Eval::generate_non_losing_moves(next);

    C4Node child(next, -curr.beta, -curr.alpha, curr.depth + 1, 0,
                 next_possible, static_cast<uint8_t>(popcount(next_possible)),
                 -32000, move);
    s.push(child);
  }

  return 0ULL;
}

Bitboard Search::solve(const Position &pos, int depth) {
  // If a winning move is available, dont go into negamax.
  if (Eval::can_win_next(pos)) {
    return 1ULL << lsb(Eval::winning_position(pos) & MoveGen::possible(pos));
  }
  return negamax(pos, -32001, 32001, depth);
}
} // namespace ConnectFour
