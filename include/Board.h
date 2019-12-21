#pragma once

#include "macros.h"
#include "Parameters.h"

struct Sequence
{
	std::vector<uint16_t>	stone;
	size_t					len;
	uint8_t					blocked;
};

enum Direction
{
	Left = -1,
	Right = 1,
	Up = -19,
	Down = 19
};

typedef std::array<std::vector<uint16_t>, 2>	indexes_t;

static int 	dirs[8] = {Left, Up + Left, Up, Up + Right, Right, Right + Down, Down, Down + Left};

class Board
{

	public:

		indexes_t				indexes;
		board_t					cells;
		std::array<uint8_t, 2>	capture;

		Board();
		~Board();

		Board					clone();
		void					add(size_t index, uint8_t player);
		uint8_t					get(size_t index);
		bool					is_double_freethree(int index, uint8_t player);
		void					remove(size_t index, uint8_t player);
		void					update(board_t new_board);
		bool					is_draw();
		void					clear_cells();
		void					clear_indexes();
		board_t					get_board();
		void					generate_indexes(board_t &new_board);
		void					capture_if_possible(int index, uint8_t player);
		bool					can_capture_win_sequence(int start, uint8_t player, int direction);
		Sequence				get_sequence(int start, uint8_t player, int direction, bool check_capture = false);
		Sequence				get_best_sequence(int start, uint8_t player, int direction);
		bool					within_limits(int start, int index, int direction);
		int						opposed_direction(int direction);
		void					play_move(size_t index, uint8_t player, Rule rule);
		bool					can_place(size_t index, uint8_t player, Rule rule);
		void					get_neighbors(int index, std::vector<uint16_t> &neighbors, board_t &checked);
		void					add_neighbor(int origin, int neighbor, int direction, std::vector<uint16_t> &neighbors, board_t &checked);

};