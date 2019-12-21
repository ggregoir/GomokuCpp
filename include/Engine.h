#pragma once

#include "Board.h"
#include "macros.h"

struct Node
{
	Board		board;
	int			score;
	uint16_t	move;
};

class Engine
{

	public:

		uint8_t		cell_value[BOARD_CAPACITY];
		int			sequence_value[7];
		int			capture_value[6];
		Rule		rule;

		Engine(Rule rule);
		~Engine();

		size_t				get_best_move(Board &board, uint8_t player);
		int					evaluate_board(Board &board, uint8_t current_player);
		std::vector<Node>	generate_sorted_children(Board &board, uint8_t player);

};