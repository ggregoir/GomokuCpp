#pragma once

#include "Board.h"
#include "Parameters.h"

#include <string>

enum PlayerMode
{
	Engine,
	Human
};

struct History
{
	board_t	board;
	int		last_move;
};

class GameManager
{

	private:
	/* data */

	public:
		GameManager(Parameters params);
		~GameManager();

		Parameters				params;
		Board					board;
		std::vector<History>	history;
		bool					player;
		uint8_t					player_mode;

		void					run_loop();
		bool					can_place(size_t index, uint8_t player);
		void					change_player_turn();
		std::string				current_player_color();
		size_t					get_connect4_index(size_t index);
		void					play_move(size_t index, uint8_t player);
		void					add_in_history(board_t board, int last_move);
		int						get_last_move();

		// temporary
		size_t					dumb_algo(board_t grid);
};
