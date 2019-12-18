#include "Board.h"
#include <algorithm>

using namespace std;

static int 	dirs[8] = {Left, Up + Left, Up, Up + Right, Right, Right + Down, Down, Down + Left};

// static int	scoring_table[9] =
// {
// 	0,		// None
// 	-30,	// BlockedTwo
// 	10,		// FreeTwo
// 	15,		// BlockedThree,
// 	50,		// BlockedFour
// 	75,		// FreeThree
// 	150,	// FreeFour
// 	160,	// Five
// 	30,		// Capture
// };

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

SeqType	Board::sum_to_sequence(uint8_t sum, bool space, uint8_t blocked)
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
		count += (sequence.type == FreeTwo);
		if (count >= 2)
			return true;
	}
	return false;
}

bool		Board::can_capture_win_sequence(int start, uint8_t player, int direction)
{
	int		offset = 0;
	int		current_dir = direction;
	uint8_t	capture_count = 0;

	for (int _loop = 0; _loop < 2; _loop++)
	{
		while (within_limits(start, start + offset, current_dir) && cells[start + offset] == player + 1)
		{
			for (int i = 0; i < 8; i++)
			{
				if (can_capture(start, player, dirs[i]))
					capture_count += 1;
			}
			offset += current_dir;
		}
		current_dir = opposed_direction(direction);
		offset = current_dir;
	}
	return (capture[1 - player] + capture_count >= 5) ? true : false;
}


Sequence	Board::get_sequence(int start, uint8_t player, int direction)
{
	Sequence	sequence;
	int			offset = 0;
	uint8_t		blocked = 0;
	bool		space = false;

	sequence.direction = direction;
	for (int _loop = 0; _loop < 2; _loop++)
	{
		while (within_limits(start, start + offset, direction))
		{
			if (cells[start + offset] == Empty)
			{
				// If next one is a player stone
				if (space == false &&
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
	sequence.type = sum_to_sequence(sequence.stone.size(), space, blocked);
	return sequence;
}

Sequence	Board::get_best_sequence(int start, uint8_t player, int direction)
{
	auto first_sequence = get_sequence(start, player, direction);
	auto second_sequence = get_sequence(start, player, opposed_direction(direction));
	if (first_sequence.type > second_sequence.type)
		return first_sequence;
	return second_sequence;
}

bool		Board::can_capture(int start, uint8_t player, int direction)
{
	if (within_limits(start, start + (direction * 3), direction))
	{
		if (cells[start + direction] == player + 1
			&& cells[start + direction + direction] == player + 1
			&& cells[start + (direction * 3)] == (1 - player) + 1)
			return true;
	}
	return false;
}

void		Board::capture_if_possible(int index, uint8_t player)
{
	for (int i = 0; i < 8; i++)
	{
		if (can_capture(index, player, dirs[i]))
		{
			remove(index + dirs[i], player);
			remove(index + dirs[i] + dirs[i], player);
			capture[1 - player] += 1;
		}
	}
}

// vector<SeqType>	Board::get_all_stone_sequence(int start, uint8_t player)
// {
// 	vector<SeqType>	seq_list;
// 	board_t				visited;


// }

// int				Board::evaluate()
// {

// }

// vector<Board>	Board::generate_sorted_children()
// {
// 	vector<Board>	children;

	
// 	return children;
// }