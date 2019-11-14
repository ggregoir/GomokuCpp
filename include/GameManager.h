#pragma once

#include "Board.h"

class GameManager
{

	public:

		GameManager();
		~GameManager();

		Board		board;
		history_t	history;
		bool		turn;

		bool		modify_board(uint32_t new_index, uint8_t color);
		uint32_t	get_last_move();
		Board		get_board();
		void		change_turn();
		uint8_t		get_turn_color();

		bool		aligned_stones(uint8_t color, uint8_t n, uint32_t direction);
};
