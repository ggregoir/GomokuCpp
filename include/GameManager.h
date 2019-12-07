#pragma once

#include "Board.h"
#include "Parameters.h"

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
		GameManager(Parameters params);
		~GameManager();

		Board		board;
		history_t	history;
		bool		turn;
		bool		player;

		bool		modify_board(uint32_t new_index, uint8_t color, bool c4_rule);
		uint32_t	get_last_move();
		Board		get_board();
		bool		get_player();
		void		change_player(Parameters &params);
		uint8_t		get_turn_color();
};
