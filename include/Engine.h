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
		int			max_depth;
		uint16_t	best_move;
		Rule		rule;
		// Algorithm	algo;

		// DEBUG
		int			nb_eval;

		Engine(Rule rule);
		~Engine();

		size_t				get_best_move(Board board, uint8_t player, Algorithm algo);
		int					evaluate_board(Board &board, uint8_t current_player);
		std::vector<Node>	generate_children(Board &board, uint8_t player);
		void				sort_children(std::vector<Node> &children, uint8_t player);

		int					pvs(Node node, int depth, int alpha, int beta, uint8_t color);
		int					negamax_abp(Node node, int depth, int alpha, int beta, uint8_t player);
		int					negamax(Node node, int depth, uint8_t player);
		int					minimax_abp(Node node, int depth, int alpha, int beta, uint8_t player);
		int					minimax(Node node, int depth, uint8_t player);

};