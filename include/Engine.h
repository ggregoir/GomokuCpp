#pragma once

#include "Board.h"

class Engine
{

	public:

		uint8_t		cell_value[BOARD_CAPACITY];
		int			sequence_value[7];
		int			capture_value[6];
		bool		restricted_mode;

		Engine(Rule rule);
		~Engine();

		int			get_best_move();
		int			evaluate_board(Board &board, uint8_t current_player);

};