#include "Board.h"

using namespace std;

Board::Board()
{
	for (auto i = 0; i < BIT_BOARD_CAPACITY; i++) bit_board[i] = 0;
}

Board::~Board() {}

uint8_t		Board::operator[](uint32_t index)
{
	return (bit_board[index * 2 / 8] >> (index * 2 % 8)) & 0B11;
}

void		Board::update(uint32_t index, uint8_t value)
{
	auto bit_index = index * 2 / 8;
	auto offset = index * 2 % 8;

	// clearing bit pair
	bit_board[bit_index] &= ~(0B11 << offset);
	// setting bit pair to value
	bit_board[bit_index] |= value << offset;
}

static uint64_t	g_mask[8] =
{
	0X5555555555555555, 0X55555555, 0X5555, 0X55, // masks to find a black stone
	0XAAAAAAAAAAAAAAAA, 0XAAAAAAAA, 0XAAAA, 0xAA  // masks to find a white stone
};

int				Board::search_stone(uint8_t stone, uint8_t type_index, uint32_t start_index, bool quit)
{
	uint64_t	found_stone = 0;

	if (quit == true)
		return (int)start_index;
	while (start_index < BIT_BOARD_CAPACITY)
	{
		switch (type_index)
		{
			case 0: found_stone = (*(uint64_t*)(bit_board + start_index)) & g_mask[0 + 4 * stone];
				break;
			case 1: found_stone = (*(uint32_t*)(bit_board + start_index)) & g_mask[1 + 4 * stone];
				break;
			case 2: found_stone = (*(uint16_t*)(bit_board + start_index)) & g_mask[2 + 4 * stone];
				break;
			case 3: found_stone = bit_board[start_index] & g_mask[3 + 4 * stone];
				break;
			default:
				break;
		}
		if (found_stone != 0)
		{
			if (type_index == 3)
				quit = true;
			return search_stone(stone, type_index + 1, start_index, quit);
		}
		switch (type_index)
		{
			case 0: start_index += 8;
				break;
			case 1:	start_index += 4;
				break;
			case 2: start_index += 2;
				break;
			case 3: start_index += 1;
				break;
			default:
				break;
		}
	}
	return -1;
}