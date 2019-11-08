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

				std::array<uint8_t, BOARD_CAPACITY>		board;

			public:

				Board();
				~Board();

				uint8_t	&operator()(int x, int y);
				uint8_t	&operator()(Position pos);
				Board	&operator=(uint8_t value);
		}

	public:

		GameManager();
		~GameManager();

		Board		board;
		history_t	history;
		bool		turn;

		bool		modify_board(uint32_t new_index, Stone color);
		uint32_t	get_last_move();
		board_t		get_board();
		void		change_turn();
		Stone		get_turn_color();
};
