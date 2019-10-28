#pragma once

#include <tuple>
#include <vector>
#include <array>

enum Stone
{
	Empty,
	Black,
	White
};

class GameManager
{

	private:
	/* data */

	public:
		GameManager();
		~GameManager();

		std::array<uint8_t, 361>					board;
		std::vector<std::tuple<uint32_t, Stone>>	history;

		bool		modify_board(uint32_t new_index, Stone color);
		uint32_t	get_last_move();
};
