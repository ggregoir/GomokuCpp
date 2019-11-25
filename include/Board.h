#pragma once

#include "macros.h"

class Board
{
	private:

		uint8_t	bit_board[BIT_BOARD_CAPACITY];

	public:

		Board();
		~Board();

		uint8_t	operator[](uint32_t index);
		void	update(uint32_t index, uint8_t value);

		int			search_stone(uint8_t stone, uint8_t type_index = 0, uint32_t start_index = 0, bool quit = false);
};