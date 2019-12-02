#pragma once

#include "macros.h"
#include "Index.h"

class Board
{
	private:

		uint8_t		bit_board[BIT_BOARD_CAPACITY];

	public:

		Board();
		~Board();

		uint8_t		operator[](uint32_t index);
		void		update(uint32_t index, uint8_t value);

		Index		search_stone(uint8_t stone, Index start, uint8_t type_index = 0, bool quit = false);
		std::vector<uint32_t>	get_stones(uint8_t stone);

};