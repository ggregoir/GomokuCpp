#pragma once

#include "macros.h"

enum SeqType
{
	None,
	BlockedTwo,
	FreeTwo,
	BlockedThree,
	BlockedFour,
	FreeThree,
	FreeFour,
	Five
};

struct Sequence
{
	std::vector<uint16_t>	stone;
	SeqType					type;
	int						direction;
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

		bool		within_limits(int start, int index, int direction);
		int			opposed_direction(int direction);
		SeqType		sum_to_sequence(uint8_t sum, bool space, uint8_t blocked);

	public:

		board_t					cells;
		std::array<uint8_t, 2>	capture;

		Board();
		~Board();

		Board				clone();
		void				add(size_t index, uint8_t player);
		uint8_t				get(size_t index);
		bool				is_double_freethree(int index, uint8_t player);
		void				remove(size_t index, uint8_t player);
		void				update(board_t new_board);
		bool				is_draw();
		void				clear_cells();
		void				clear_indexes();
		board_t				get_board();
		void				generate_indexes(board_t &new_board);
		void				capture_if_possible(int index, uint8_t player);
		bool				can_capture_win_sequence(int start, uint8_t player, int direction);
		Sequence			get_sequence(int start, uint8_t player, int direction);
		Sequence			get_best_sequence(int start, uint8_t player, int direction);

		// int					evaluate();
		// std::vector<Board>	generate_sorted_children();
		// std::vector<SeqType>	get_all_stone_sequence(int start, uint8_t player);

};