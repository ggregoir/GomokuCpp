#pragma once


#include "macros.h"

#include <tuple>
#include <vector>
#include <array>

enum Stone
{
	Empty,
	Black,
	White
};

class GameManager
{

	private:

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

	public:

		GameManager();
		~GameManager();

		Board		board;
		history_t	history;
		bool		turn;

		bool		modify_board(uint32_t new_index, Stone color);
		uint32_t	get_last_move();
		Board		get_board();
		void		change_turn();
		Stone		get_turn_color();
};
