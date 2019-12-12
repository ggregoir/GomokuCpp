#pragma once

#include "macros.h"

enum Sequence
{
	None,
	BlockedTwo,
	FreeTwo,
	BlockedThree,
	FreeThree,
	BlockedFour,
	FreeFour,
	Five
};

enum Direction
{
	Left = -1,
	Right = 1,
	Up = -19,
	Down = 19
};

typedef std::array<std::vector<uint16_t>, 2>	indexes_t;

class Board
{
	private:

		indexes_t	indexes;
		uint8_t*	board = nullptr;

		bool		within_limits(int start, int index, int direction);
		int			opposed_direction(int direction);
		uint8_t		half_sequence(int start, uint8_t player, int direction, bool &space, uint8_t &block);

	public:

		Board();
		~Board();

		void		add(size_t index, uint8_t player);
		uint8_t		get(size_t index);
		void		remove(size_t index);
		void		update(board_t new_board);
		int			is_draw();
		void		clear_board();
		void		clear_indexes();
		board_t		get_board();
		void		generate_indexes(board_t &new_board);
		void		generate_board(indexes_t &indexes);
		Sequence	get_stone_sequence(int start, uint8_t player, int direction);

};