#pragma once

#include "Board.h"

enum PlayerMode
{
	AI,
	Human
};

struct History
{
	board_t						board;
	size_t						last_move;
	std::array<uint8_t, 2>		capture;
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
		void					change_player_turn();
		size_t					get_connect4_index(size_t index);
		int						get_last_move();
		void					load_history();
		void					print_game_status(uint8_t status);

};
