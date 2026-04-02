#include <cstdint>
#include <vector>

#include "bitboard.h"

namespace ConnectFour {
enum TTFlag : uint8_t { TT_EXACT, TT_LOWERBOUND, TT_UPPERBOUND };

struct TTEntry {
  uint64_t key;
  int16_t score;
  uint8_t depth;
  TTFlag flag;
  Bitboard best_move;
};

class TranspositionTable {
private:
  std::vector<TTEntry> table;
  size_t size_mask;

public:
  TranspositionTable(size_t size_mb) {
    size_t num_entries = (size_mb * 1024 * 1024) / sizeof(TTEntry);
    size_t power_of_2 = 1;
    while (power_of_2 <= num_entries) {
      power_of_2 <<= 1;
    }
    power_of_2 >>= 1;
    table.resize(power_of_2, {0, 0, 0, TT_EXACT, 0ULL});
    size_mask = power_of_2 - 1;
  }

	void store(uint64_t key, int16_t score, uint8_t depth, TTFlag flag, Bitboard best_move) {
		size_t index = key & size_mask;

		if (table[index].key == 0 || depth >= table[index].depth) {
			table[index] = {key, score, depth, flag, best_move};
		}
	}

	bool probe(uint64_t key, TTEntry &entry) {
		size_t index = key & size_mask;
		if (table[index].key == key) {
			entry = table[index];
			return true;
		}
		return false;
	}


};
} // namespace ConnectFour
