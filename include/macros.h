#pragma once

#include <tuple>
#include <vector>
#include <array>

class Position;

#define BOARD_SIZE		19
#define BOARD_CAPACITY	(BOARD_SIZE * BOARD_SIZE)

#define POS_TO_INDEX(pos) (pos.y * BOARD_SIZE + pos.x)
#define INDEX_TO_POS(i) (Position { (int)i % BOARD_SIZE, (int)i / BOARD_SIZE })

typedef std::array<uint8_t, BOARD_CAPACITY>			board_t;
typedef std::vector<std::tuple<uint32_t, uint8_t>>	history_t;