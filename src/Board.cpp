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

Board			Board::clone()
{
	return *this;
}

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

void		Board::update(board_t new_board)
{
	cells = new_board;
	generate_indexes(new_board);
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

bool		Board::is_draw()
{
	int total = 0;
	total = indexes[0].size();
	total += indexes[1].size();
	return (total == BOARD_CAPACITY) ? true : false;
}

bool		Board::is_double_freethree(int index, uint8_t player)
{
	uint8_t	count = 0;

	for (int i = 0; i < 4; i++)
	{
		auto sequence = get_sequence(index, player, dirs[i]);
		count += (sequence.len == 2 && sequence.blocked == 0);
		if (count >= 2)
			return true;
	}
	return false;
}

bool		Board::can_capture_win_sequence(int start, uint8_t player, int direction)
{
	int		offset = 0;
	int		current_dir = direction;
	int		abs_dir = direction * (direction < 0 ? 1 : -1);
	uint8_t	capture_count = 0;

	for (int _loop = 0; _loop < 2; _loop++)
	{
		while (within_limits(start, start + offset, current_dir) && cells[start + offset] == player + 1)
		{
			for (int i = 0; i < 4; i++)
			{
				if (dirs[i] != abs_dir)
				{
					auto sequence = get_sequence(start + offset, player, dirs[i], true);
					if (sequence.len == 2 && sequence.blocked == 1)
						capture_count += 1;
				}
			}
			offset += current_dir;
		}
		current_dir = opposed_direction(direction);
		offset = current_dir;
	}
	return (capture[player ^ 1] + capture_count >= 5) ? true : false;
}


Sequence	Board::get_sequence(int start, uint8_t player, int direction, bool check_capture)
{
	Sequence	sequence;
	int			offset = 0;
	uint8_t		blocked = 0;
	bool		space = false;

	for (int _loop = 0; _loop < 2; _loop++)
	{
		while (within_limits(start, start + offset, direction))
		{
			if (cells[start + offset] == Empty)
			{
				if (check_capture == true)
					break;
				// If next one is a player stone
				else if (space == false &&
					within_limits(start, start + offset + direction, direction) &&
					cells[start + offset + direction] == player + 1)
				{
					if (offset != 0)
						space = true;
				}
				else
					break;
			}
			else if (cells[start + offset] != player + 1)
			{
				blocked += 1;
				break;
			}
			else
			{
				if (sequence.stone.size() == 4 && space == true)
					break;
				sequence.stone.push_back(start + offset);
			}
			offset += direction;
		}
		direction = opposed_direction(direction);
		offset = direction;
	}
	if (blocked > 1 || sequence.stone.size() < 2)
		sequence.len = 0;
	else if (sequence.stone.size() == 2 && space == true)
		sequence.len = 0;
	else
		sequence.len = sequence.stone.size();
	sequence.blocked = (sequence.len != 5) ? blocked : 0;
	return sequence;
}

Sequence	Board::get_best_sequence(int start, uint8_t player, int direction)
{
	auto first_seq = get_sequence(start, player, direction);
	auto second_seq = get_sequence(start, player, opposed_direction(direction));

	if (first_seq.len > second_seq.len)
		return first_seq;
	else if (first_seq.len < second_seq.len)
		return second_seq;
	else if (first_seq.blocked <= second_seq.blocked)
		return first_seq;
	return second_seq;
}

void		Board::capture_if_possible(int index, uint8_t player)
{
	for (int i = 0; i < 8; i++)
	{
		if (within_limits(index, index + (dirs[i] * 3), dirs[i]))
		{
			if (cells[index + dirs[i]] == player + 1
				&& cells[index + dirs[i] + dirs[i]] == player + 1
				&& cells[index + (dirs[i] * 3)] == (player ^ 1) + 1)
			{
				remove(index + dirs[i], player);
				remove(index + dirs[i] + dirs[i], player);
				capture[player ^ 1] += 1;
			}
		}
	}
}

void		Board::play_move(size_t index, uint8_t player, Rule rule)
{
	if (rule == Restricted)
		capture_if_possible(index, player ^ 1);
	add(index, player);
}

bool		Board::can_place(size_t index, uint8_t player, Rule rule)
{
	if (cells[index] != Empty)
		return false;
	if (rule == Restricted && is_double_freethree(index, player))
		return false;
	return true;
}

void		Board::add_neighbor(int origin, int neighbor, int direction, vector<uint16_t> &neighbors, board_t &checked)
{
	if (checked[neighbor] == Empty && cells[neighbor] == Empty && within_limits(origin, neighbor, direction))
	{
		neighbors.push_back((uint16_t)neighbor);
		checked[neighbor] = 1;
	}
}

void		Board::get_neighbors(int index, vector<uint16_t> &neighbors, board_t &checked)
{
	// 1st row
	add_neighbor(index, index + (Up + Left) * 2, Up + Left, neighbors, checked);
	add_neighbor(index, index + Up * 2 + Left, Up + Left, neighbors, checked);
	add_neighbor(index, index + Up * 2, Up, neighbors, checked);
	add_neighbor(index, index + Up * 2 + Right, Up + Right, neighbors, checked);
	add_neighbor(index, index + (Up + Right) * 2, Up + Right, neighbors, checked);
	// 2nd row
	add_neighbor(index, index + Left * 2 + Up, Up + Left, neighbors, checked);
	add_neighbor(index, index + Up + Left, Up + Left, neighbors, checked);
	add_neighbor(index, index + Up, Up, neighbors, checked);
	add_neighbor(index, index + Up + Right, Up + Right, neighbors, checked);
	add_neighbor(index, index + Right * 2 + Up, Up + Right, neighbors, checked);
	// 3rd row
	add_neighbor(index, index + Left * 2, Left, neighbors, checked);
	add_neighbor(index, index + Left, Left, neighbors, checked);
	add_neighbor(index, index + Right, Right, neighbors, checked);
	add_neighbor(index, index + Right * 2, Right, neighbors, checked);
	// 4th row
	add_neighbor(index, index + Left * 2 + Down, Down + Left, neighbors, checked);
	add_neighbor(index, index + Down + Left, Down + Left, neighbors, checked);
	add_neighbor(index, index + Down, Down, neighbors, checked);
	add_neighbor(index, index + Down + Right, Down + Right, neighbors, checked);
	add_neighbor(index, index + Right * 2 + Down, Down + Right, neighbors, checked);
	// 5th row
	add_neighbor(index, index + (Down + Left) * 2, Down + Left, neighbors, checked);
	add_neighbor(index, index + Down * 2 + Left, Down + Left, neighbors, checked);
	add_neighbor(index, index + Down * 2, Down, neighbors, checked);
	add_neighbor(index, index + Down * 2 + Right, Down + Right, neighbors, checked);
	add_neighbor(index, index + (Down + Right) * 2, Down + Right, neighbors, checked);
}