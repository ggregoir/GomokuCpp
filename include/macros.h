#pragma once

#include <tuple>
#include <vector>
#include <array>

class Position;

enum Stone
{
	Empty,
	Black,
	White
};

#define BOARD_SIZE			19
#define BOARD_CAPACITY		(BOARD_SIZE * BOARD_SIZE)
#define BIT_BOARD_CAPACITY 	(BOARD_CAPACITY * 2 / 8) + 1

#define INDEX_TO_POS(i) (Position((int)i % BOARD_SIZE, (int)i / BOARD_SIZE))

typedef std::array<uint8_t, BOARD_CAPACITY>		board_t;