#pragma once

#include "Board.h"

enum PlayerMode
{
	AI,
	Human
};

enum GameStatus
{
	Playing,
	PlayerOneWin,
	PlayerTwoWin,
	PlayerOneWinByCapture,
	PlayerTwoWinByCapture,
	Draw
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
		GameStatus				is_endgame(int index, uint8_t player);
		void					print_game_status(GameStatus status);

		// temporary
		size_t					dumb_algo(board_t grid);
};
