#pragma once

#include "Board.h"
#include "Parameters.h"

#include <string>

enum Stone
{
	Empty,
	Black,
	White
};

enum PlayerMode
{
	Engine,
	Human
};

class GameManager
{

	private:
	/* data */

	public:
		GameManager(Parameters params);
		~GameManager();

		Parameters	params;
		Board		board;
		history_t	history;
		bool		turn;
		bool		player;

		void		run_loop();
		bool		modify_board(uint32_t new_index, uint8_t color, bool c4_rule);
		uint32_t	get_last_move();
		Board		get_board();

		bool		player_mode();
		uint8_t		current_color();
		void		change_player_turn();
		std::string	current_color_name();
		std::string	player_mode_name();
};
