#include "Board.h"
#include <algorithm>

using namespace std;

Board::Board() {}

Board::~Board()
{
	if (board != nullptr)
		delete []board;
}

void	Board::add(size_t index, uint8_t player)
{
	if (board != nullptr)
		board[index] = player + 1;
	indexes[player].push_back(index);
}

uint8_t	Board::get(size_t index)
{
	for (uint8_t player = 0; player < 2; player++)
	{
		for (size_t i = 0; i < indexes[player].size(); i++)
		{
			if (indexes[player][i] == index)
				return player + 1;
		}
	}
	return 0;
}

void	Board::remove(size_t index)
{
	for (auto & vec : indexes)
	{
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (vec[i] == index)
				vec.erase(vec.begin() + i);
		}
	}
	if (board == nullptr)
		board[index] = 0;
}

void	Board::clear_board()
{
	if (board != nullptr)
	{
		delete []board;
		board = nullptr;
	}
}

void	Board::clear_indexes()
{
	indexes[0].clear();
	indexes[1].clear();
}

int	Board::is_draw()
{
	int total = 0;
	total = indexes[0].size();
	total += indexes[1].size();
	if (total == 361)
		return(1);
	else
		return(0);
}

board_t	Board::get_board()
{
	board_t	new_board;

	if (board == nullptr)
		generate_board(indexes);
	std::copy(board, board + BOARD_CAPACITY, new_board.begin());
	return new_board;
}

void	Board::update(board_t new_board)
{
	clear_board();
	clear_indexes();
	board = new uint8_t[BOARD_CAPACITY];
	std::copy(new_board.begin(), new_board.end(), board);
	generate_indexes(new_board);
}

void	Board::generate_indexes(board_t &new_board)
{
	if (indexes[0].size() > 0 || indexes[1].size() > 0)
		clear_indexes();
	for (size_t i = 0; i < BOARD_CAPACITY; i++)
	{
		if (new_board[i] > 0)
			indexes[new_board[i] - 1].push_back(i);
	}
}

void	Board::generate_board(indexes_t &indexes)
{
	if (board != nullptr)
		clear_board();
	board = new uint8_t[BOARD_CAPACITY];
	std::fill(board, board + BOARD_CAPACITY, 0);
	for (uint8_t player = 0; player < 2; player++)
	{
		for (size_t i = 0; i < indexes[player].size(); i++)
			board[indexes[player][i]] = player + 1;
	}
}