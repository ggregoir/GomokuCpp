#pragma once

#include "macros.h"

class Board
{
	private:

		std::array<uint8_t, BIT_BOARD_CAPACITY>		bit_board;

	public:

		Board();
		~Board();

		uint8_t	operator[](uint32_t index);
		void	update(uint32_t index, uint8_t value);
};