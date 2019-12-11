#pragma once

#include "macros.h"

typedef std::array<std::vector<uint16_t>, 2>	indexes_t;

class Board
{
	private:

		indexes_t	indexes;
		uint8_t*	board = nullptr;

	public:

		Board();
		~Board();

		void		add(size_t index, uint8_t player);
		uint8_t		get(size_t index);
		void		remove(size_t index);
		void		update(board_t new_board);
		void		clear_board();
		void		clear_indexes();
		board_t		get_board();
		void		generate_indexes(board_t &new_board);
		void		generate_board(indexes_t &indexes);

};