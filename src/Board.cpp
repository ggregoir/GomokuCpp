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
	auto bit_index = index * 2;
	auto byte_index = bit_index / 8;
	auto offset = index * 2 % 8;

	// clearing bit pair
	bit_board[byte_index] &= ~(0B11 << offset);
	// setting bit pair to value
	bit_board[byte_index] |= value << offset;
}

static uint64_t	g_mask[8] =
{
	0X5555555555555555, 0X55555555, 0X5555, 0X55, // masks to find a black stone
	0XAAAAAAAAAAAAAAAA, 0XAAAAAAAA, 0XAAAA, 0xAA  // masks to find a white stone
};

static int8_t	get_offset(uint8_t byte, uint8_t offset, uint8_t stone)
{
	if ((byte >> offset) & g_mask[3 + 4 * stone])
	{
		while (offset < 8)
		{
			if ((byte >> offset) & (stone + 1))
				return (int8_t)offset;
			offset += 2;
		}
	}
	return -1;
}

Index			Board::search_stone(uint8_t stone, Index start, uint8_t type_index, bool quit)
{
	uint64_t	found_stone = 0;

	if (start.offset != 0)
	{
		auto offset = get_offset(bit_board[start.byte], start.offset, stone);
		if (offset < 0)
			start.byte += 1;
		else
			return Index { start.byte, (uint8_t)offset };
	}
	if (quit == true)
		return start;
	while (start.byte < BIT_BOARD_CAPACITY)
	{
		switch (type_index)
		{
			case 0: found_stone = (*(uint64_t*)(bit_board + start.byte)) & g_mask[0 + 4 * stone];
				break;
			case 1: found_stone = (*(uint32_t*)(bit_board + start.byte)) & g_mask[1 + 4 * stone];
				break;
			case 2: found_stone = (*(uint16_t*)(bit_board + start.byte)) & g_mask[2 + 4 * stone];
				break;
			case 3: found_stone = bit_board[start.byte] & g_mask[3 + 4 * stone];
				break;
			default:
				break;
		}
		if (found_stone != 0)
		{
			if (type_index == 3)
			{
				start.offset = (uint8_t)get_offset(bit_board[start.byte], start.offset, stone);
				quit = true;
			}
			return search_stone(stone, start, type_index + 1, quit);
		}
		start.offset = 0;
		switch (type_index)
		{
			case 0: start.byte += 8;
				break;
			case 1:	start.byte += 4;
				break;
			case 2: start.byte += 2;
				break;
			case 3: start.byte += 1;
				break;
			default:
				break;
		}
	}
	return Index { -1, 0 };
}

vector<uint32_t>	Board::get_stones(uint8_t stone)
{
	Index				current;
	vector<uint32_t>	stone_list;
	
	while (true)
	{
		current = search_stone(stone, current);
		if (current.byte < 0)
			break;
		stone_list.push_back(current.byte * 4 + current.offset / 2);
		current.increment();
	}
	return stone_list;
}