#pragma once

#include "Board.h"


enum Stone
{
	Empty,
	Black,
	White
};

class GameManager
{

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
