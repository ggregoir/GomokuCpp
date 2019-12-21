#include "Engine.h"
#include <algorithm>
#include <limits>
#include <functional>

using namespace std;

static bool (*cmp_score[2])(int, int) 
{
	[](int x, int y) { return x > y; },
	[](int x, int y) { return x < y; }
};

static bool (*cmp_node[2])(Node&, Node&) 
{
	[](Node &lhs, Node &rhs) { return cmp_score[0](lhs.score, rhs.score); },
	[](Node &lhs, Node &rhs) { return cmp_score[1](lhs.score, rhs.score); }
};


Engine::Engine(Rule rule)
{
	sequence_value[0] = 0;
	sequence_value[1] = 0;
	sequence_value[2] = 100;
	sequence_value[3] = 1000;
	sequence_value[4] = 10000;
	sequence_value[5] = 100000;
	sequence_value[6] = 100000; // To allow sequence_value[sequence.len + 1]

	capture_value[0] = 0;
	capture_value[1] = 500;
	capture_value[2] = 1000;
	capture_value[3] = 2000;
	capture_value[4] = 8000;
	capture_value[5] = 100000;

	this->rule = rule;
	for (int y = 0; y <= BOARD_SIZE / 2; y++)
	{
		for (int x = 0; x <= BOARD_SIZE / 2; x++)
		{
			auto pos_value = std::min(x, y);
			cell_value[y * BOARD_SIZE + x] = pos_value;
			cell_value[y * BOARD_SIZE + (BOARD_SIZE - 1 - x)] = pos_value;
			cell_value[(BOARD_SIZE - 1 - y) * BOARD_SIZE + (BOARD_SIZE - 1 - x)] = pos_value;
			cell_value[(BOARD_SIZE - 1 - y) * BOARD_SIZE + x] = pos_value;
		}
	}
}

Engine::~Engine() {}

int		Engine::evaluate_board(Board &board, uint8_t current_player)
{
	board_t	visited_stones;
	int		score = 0;
	uint8_t	player = 0;
	int8_t	coef = 1;
	uint8_t	diff_player = current_player != player;

	std::fill(visited_stones.begin(), visited_stones.end(), 0);
	for (auto &player_stones : board.indexes)
	{
		for (auto &stone : player_stones)
		{
			score += (cell_value[stone] * coef);
			if (visited_stones[stone] == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					auto seq = board.get_best_sequence(stone, player, dirs[i]);
					if (rule == Restricted && seq.len == 2 && seq.blocked == 1)
						score += (capture_value[board.capture[player ^ 1]] * -coef);
					else
						score += (sequence_value[seq.len + diff_player] / (1 + seq.blocked + diff_player) * coef);
					for (auto &index : seq.stone)
						visited_stones[index] = 1;
				}
			}
		}
		score += (capture_value[board.capture[player]] * coef);
		coef = -1;
		player = 1;
		diff_player = current_player != player;
	}
	return score;
}

vector<Node>	Engine::generate_sorted_children(Board &board, uint8_t player)
{
	vector<Node>		children;
	vector<uint16_t>	neighbors;
	board_t 			checked;

	std::fill(checked.begin(), checked.end(), Empty);
	for (auto &player_stones : board.indexes)
	{
		for (auto &stone : player_stones)
			board.get_neighbors((int)stone, neighbors, checked);
	}
	for (auto & index : neighbors)
	{
		auto new_board = board.clone();
		if (new_board.can_place(index, player, rule))
			new_board.play_move(index, player, rule);
		auto score = evaluate_board(new_board, player);
		children.push_back(Node {new_board, score, index});
	}
	std::sort(children.begin(), children.end(), cmp_node[player]);
	return children;
}

size_t	Engine::get_best_move(Board &board, uint8_t player)
{
	size_t	best_move = 0;
	int		best_score = (player + 1 == Black)
		? std::numeric_limits<int>::min()
		: std::numeric_limits<int>::max();

	// If first turn then return center position
	if (board.indexes[0].size() == 0 && board.indexes[1].size() == 0)
		return BOARD_CAPACITY / 2;
	auto children = generate_sorted_children(board, player);
	for (auto & child : children)
	{
		if (cmp_score[player](child.score, best_score))
		{
			best_score = child.score;
			best_move = child.move;
		}
	}
	return best_move;
}