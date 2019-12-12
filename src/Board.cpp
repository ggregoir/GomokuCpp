#include "Board.h"
#include <algorithm>

using namespace std;

Board::Board() {}

Board::~Board()
{
	if (board != nullptr)
		delete []board;
}

void		Board::add(size_t index, uint8_t player)
{
	if (board != nullptr)
		board[index] = player + 1;
	indexes[player].push_back(index);
}

uint8_t		Board::get(size_t index)
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

void		Board::remove(size_t index)
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

void		Board::clear_board()
{
	if (board != nullptr)
	{
		delete []board;
		board = nullptr;
	}
}

void		Board::clear_indexes()
{
	indexes[0].clear();
	indexes[1].clear();
}

int			Board::is_draw()
{
	int total = 0;
	total = indexes[0].size();
	total += indexes[1].size();
	if (total == 361)
		return(1);
	else
		return(0);
}

board_t		Board::get_board()
{
	board_t	new_board;

	if (board == nullptr)
		generate_board(indexes);
	std::copy(board, board + BOARD_CAPACITY, new_board.begin());
	return new_board;
}

void		Board::update(board_t new_board)
{
	clear_board();
	clear_indexes();
	board = new uint8_t[BOARD_CAPACITY];
	std::copy(new_board.begin(), new_board.end(), board);
	generate_indexes(new_board);
}

void		Board::generate_indexes(board_t &new_board)
{
	if (indexes[0].size() > 0 || indexes[1].size() > 0)
		clear_indexes();
	for (size_t i = 0; i < BOARD_CAPACITY; i++)
	{
		if (new_board[i] > 0)
			indexes[new_board[i] - 1].push_back(i);
	}
}

void		Board::generate_board(indexes_t &indexes)
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

bool		Board::within_limits(int start, int index, int direction)
{
	if (direction == Left || direction == Right)
		return start / BOARD_SIZE == index / BOARD_SIZE;
	else if (direction == Up)
		return index >= 0;
	else if (direction == Down)
		return index < BOARD_CAPACITY;
	else if (direction == Up + Left)
		return (index >= 0) && (start % BOARD_SIZE > index % BOARD_SIZE);
	else if (direction == Down + Right)
		return (index < BOARD_CAPACITY) && (start % BOARD_SIZE < index % BOARD_SIZE);
	else if (direction == Up + Right)
		return (index >= 0) && (start % BOARD_SIZE < index % BOARD_SIZE);
	else if (direction == Down + Left)
		return (index < BOARD_CAPACITY) && (start % BOARD_SIZE > index % BOARD_SIZE);
	return false;
}

int			Board::opposed_direction(int direction)
{
	if (direction == Left)
		return Right;
	else if (direction == Right)
		return Left;
	else if (direction == Up)
		return Down;
	else if (direction == Down)
		return Up;
	else if (direction == Up + Left)
		return Down + Right;
	else if (direction == Down + Right)
		return Up + Left;
	else if (direction == Up + Right)
		return Down + Left;
	else if (direction == Down + Left)
		return Up + Right;
	return direction;
}

uint8_t		Board::half_sequence(int start, uint8_t player, int direction, bool &space, uint8_t &blocked)
{
	uint8_t	sum = 0;
	int		i = direction;

	while (within_limits(start, start + i, direction))
	{
		if (board[start + i] == Empty && space == false)
		{
			if (space == false)
				space = true;
			else
				return sum;
		}
		else if (board[start + i] != player + 1)
		{
			blocked += 1;
			return sum;
		}
		else
			sum += 1;
		i += direction;
	}
	return sum;
}

Sequence	Board::get_stone_sequence(int start, uint8_t player, int direction)
{
	uint8_t	sum = 0;
	bool	space = false;
	uint8_t	blocked = 0;

	if (board == nullptr)
		generate_board(indexes);
	if (board[start] == Empty)
		space = true;
	else if (board[start] != player + 1)
		return None;
	else
		sum += 1;
	
	sum += half_sequence(start, player, direction, space, blocked);
	sum += half_sequence(start, player, opposed_direction(direction), space, blocked);
	
	if (sum < 2 || blocked > 1)
		return None;
	else if (sum == 2)
		return blocked ? BlockedTwo : FreeTwo;
	else if (sum == 3)
		return blocked ? BlockedThree : FreeThree;
	else if (sum == 4)
		return blocked ? BlockedFour : FreeFour;
	else if (sum >= 5)
		return Five;
	return None;
}