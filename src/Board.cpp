#include "Board.h"
#include <algorithm>

using namespace std;

Board::Board()
{
	capture[0] = 0;
	capture[1] = 0;
	clear_cells();
}

Board::~Board() {}

void		Board::add(size_t index, uint8_t player)
{
	cells[index] = player + 1;
	indexes[player].push_back(index);
}

uint8_t		Board::get(size_t index)
{
	return cells[index];
}

void		Board::remove(size_t index, uint8_t player)
{
	for (size_t i = 0; i < indexes[player].size(); i++)
	{
		if (indexes[player][i] == index)
			indexes[player].erase(indexes[player].begin() + i);
	}
	cells[index] = 0;
}

void		Board::clear_cells()
{
	std::fill(cells.begin(), cells.end(), 0);
}

void		Board::clear_indexes()
{
	indexes[0].clear();
	indexes[1].clear();
}

bool		Board::is_draw()
{
	int total = 0;
	total = indexes[0].size();
	total += indexes[1].size();
	return (total == BOARD_CAPACITY) ? true : false;
}

void		Board::update(board_t new_board)
{
	cells = new_board;
	generate_indexes(new_board);
}

static int 	dirs[8] = {Left, Up + Left, Up, Up + Right, Right, Right + Down, Down, Down + Left};

bool	Board::check_double_freethree(int index, uint8_t player)
{
	int		direction = 0;
	bool	space = false;
	uint8_t	blocked = 0;
	uint8_t	sum = 0;

	for (int i = 0; i < 8; i++)
	{
		sum = half_sequence(index, player, dirs[i], space, blocked, 0);
		if (direction == 0)
		{
			if (sum_to_sequence(sum, space, blocked) == FreeTwo)
				direction = dirs[i];
		}
		else if (sum_to_sequence(sum, space, blocked) == FreeTwo)
			return opposed_direction(dirs[i]) != direction;
		blocked = 0;
		space = false;
	}
	return false;
}

bool		Board::can_capture_win_sequence(int start, uint8_t player, int direction)
{
	int		i = 0;
	int		tmp_dir = direction;
	bool	space = false;
	uint8_t	blocked = 0;
	uint8_t	capture_count = 0;

	while (true)
	{
		if (!within_limits(start, start + i, tmp_dir) || cells[start + i] != player + 1)
		{
			if (tmp_dir != direction)
				break;
			tmp_dir = opposed_direction(direction);
			i = tmp_dir;
		}
		for (int i_dir = 0; i_dir < 4; i_dir++)
		{
			auto op_dir = opposed_direction(dirs[i_dir]);
			auto sum = half_sequence(start + i, player, dirs[i_dir], space, blocked, cells[start + i] == player + 1);
			sum += half_sequence(start + i, player, op_dir, space, blocked, 0);
			if (sum_to_sequence(sum, space, blocked) == BlockedTwo)
				capture_count += 1;
			blocked = 0;
			space = false;
		}
		i += tmp_dir;
	}
	return (capture[1 - player] + capture_count >= 5) ? true : false;
}

void		Board::check_capture(int index, uint8_t player)
{
	bool	space = false;
	uint8_t	blocked = 0;
	uint8_t	sum = 0;

	for (int i = 0; i < 8; i++)
	{
		sum = half_sequence(index, player, dirs[i], space, blocked, 0);
		if (sum_to_sequence(sum, space, blocked) == BlockedTwo)
		{
			remove(index + dirs[i], player);
			remove(index + dirs[i] + dirs[i], player);
			capture[1 - player] += 1;
		}
		blocked = 0;
		space = false;
	}
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

bool		Board::within_limits(int start, int index, int direction)
{
	if (direction == Left || direction == Right)
		return start / BOARD_SIZE == index / BOARD_SIZE;
	else if (direction == Up)
		return index >= 0;
	else if (direction == Down)
		return index < BOARD_CAPACITY;
	else if (direction == Up + Left)
		return (index >= 0) && (start % BOARD_SIZE >= index % BOARD_SIZE);
	else if (direction == Down + Right)
		return (index < BOARD_CAPACITY) && (start % BOARD_SIZE <= index % BOARD_SIZE);
	else if (direction == Up + Right)
		return (index >= 0) && (start % BOARD_SIZE <= index % BOARD_SIZE);
	else if (direction == Down + Left)
		return (index < BOARD_CAPACITY) && (start % BOARD_SIZE >= index % BOARD_SIZE);
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

uint8_t		Board::half_sequence(int start, uint8_t player, int direction, bool &space, uint8_t &blocked, uint8_t sum)
{
	int		i = direction;

	while (within_limits(start, start + i, direction))
	{
		if (cells[start + i] == Empty)
		{
			if (space == false &&
				within_limits(start, start + i + direction, direction) &&
				cells[start + i + direction] == player + 1)
			{
				space = true;
			}
			else
				return sum;
		}
		else if (cells[start + i] != player + 1)
		{
			blocked += 1;
			return sum;
		}
		else
		{
			if (sum == 4 && space == true)
				return sum;
			sum += 1;
		}
		i += direction;
	}
	return sum;
}

Sequence	Board::sum_to_sequence(uint8_t sum, bool space, uint8_t blocked)
{
	if (sum < 2 || blocked > 1)
		return None;
	else if (sum == 2 && space == true)
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

Sequence	Board::stone_sequence(int start, uint8_t player, int direction)
{
	uint8_t	sum = 0;
	bool	space = false;
	uint8_t	blocked = 0;

	if (cells[start] == Empty)
		space = true;
	else if (cells[start] != player + 1)
		return None;
	else
		sum += 1;
	
	sum = half_sequence(start, player, direction, space, blocked, sum);
	sum = half_sequence(start, player, opposed_direction(direction), space, blocked, sum);
	return sum_to_sequence(sum, space, blocked);
}

Sequence	Board::get_stone_sequence(int start, uint8_t player, int direction)
{
	auto first_sequence = stone_sequence(start, player, direction);
	auto second_sequence = stone_sequence(start, player, opposed_direction(direction));
	return std::max(first_sequence, second_sequence);
}