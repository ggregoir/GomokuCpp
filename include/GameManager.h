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
	/* data */

	public:
		GameManager();
		~GameManager();

		board_t		board;
		history_t	history;
		bool		turn;

		bool		modify_board(uint32_t new_index, Stone color);
		uint32_t	get_last_move();
		board_t		get_board();
		void		change_turn();
		Stone		get_turn_color();
};
