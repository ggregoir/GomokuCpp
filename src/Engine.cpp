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
	max_depth = 3;

	sequence_value[0] = 0;
	sequence_value[1] = 0;
	sequence_value[2] = 100;
	sequence_value[3] = 1000;
	sequence_value[4] = 10000;
	sequence_value[5] = 100000;
	sequence_value[6] = 100000; // To allow sequence_value[sequence.len + 1]

	capture_value[0] = 0;
	capture_value[1] = 500;
	capture_value[2] = 2000;
	capture_value[3] = 5000;
	capture_value[4] = 20000;
	capture_value[5] = 100000;

	this->rule = rule;
	// this->algo = algo;
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
	nb_eval += 1;
	return score;
}

vector<Node>	Engine::generate_children(Board &board, uint8_t player)
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
		children.push_back(Node {new_board, 0, index});
	}
	return children;
}

void			Engine::sort_children(vector<Node> &children, uint8_t player)
{
	for (auto & node : children)
		node.score = evaluate_board(node.board, player);
	std::sort(children.begin(), children.end(), cmp_node[player]);
}

int		Engine::pvs(Node node, int depth, int alpha, int beta, uint8_t player)
{
	if (depth == 0 || node.board.is_endgame(node.move, player, rule == Restricted))
		return ((player * -2) + 1) * node.score;

	auto children = generate_children(node.board, player);
	sort_children(children, player);
	int	best_score = -pvs(children[0], depth - 1, -beta, -alpha, player ^ 1);
	for (size_t i = 1; i < children.size(); i++)
	{
		int score = -pvs(children[i], depth - 1, -alpha - 1, -alpha, player ^ 1);
		if (alpha < score && score < beta)
			score = -pvs(children[i], depth - 1, -beta, -score, player ^ 1);
		if (score > best_score)
		{
			if (depth == max_depth)
				best_move = children[i].move;
			best_score = score;
			if (score > alpha)
				alpha = score;
			if (alpha >= beta)
				break;
		}
	}
	return best_score;
}

int		Engine::negamax_abp(Node node, int depth, int alpha, int beta, uint8_t player)
{
	if (depth == 0 || node.board.is_endgame(node.move, player, rule == Restricted))
		return ((player * -2) + 1) * node.score;
	
	int	best_score = numeric_limits<int>::min();
	auto children = generate_children(node.board, player);
	sort_children(children, player);
	for (auto child_node = children.cbegin(); child_node < children.cend(); child_node++)
	{
		int score = -negamax_abp(*child_node, depth - 1, -beta, -alpha, player ^ 1);
		if (score > best_score)
		{
			if (depth == max_depth)
				best_move = child_node->move;
			best_score = score;
			if (score > alpha)
				alpha = score;
			if (alpha >= beta)
				break;
		}
	}
	return best_score;
}

int		Engine::negamax(Node node, int depth, uint8_t player)
{
	if (depth == 0 || node.board.is_endgame(node.move, player, rule == Restricted))
		return ((player * -2) + 1) * evaluate_board(node.board, player);
	
	int	best_score = numeric_limits<int>::min();
	auto children = generate_children(node.board, player);
	for (auto child_node = children.cbegin(); child_node < children.cend(); child_node++)
	{
		int score = -negamax(*child_node, depth - 1, player ^ 1);
		if (score > best_score)
		{
			if (depth == max_depth)
				best_move = child_node->move;
			best_score = score;
		}
	}
	return best_score;
}

int		Engine::minimax(Node node, int depth, uint8_t player)
{
	if (depth == 0 || node.board.is_endgame(node.move, player, rule == Restricted))
		return evaluate_board(node.board, player);
	
	if (player + 1 == Black)
	{
		int	best_score = numeric_limits<int>::min();
		auto children = generate_children(node.board, player);
		for (auto child_node = children.cbegin(); child_node < children.cend(); child_node++)
		{
			int score = minimax(*child_node, depth - 1, player ^ 1);
			if (score > best_score)
			{
				if (depth == max_depth)
					best_move = child_node->move;
				best_score = score;
			}
		}
		return best_score;
	}
	else
	{
		int	best_score = numeric_limits<int>::max();
		auto children = generate_children(node.board, player);
		for (auto child_node = children.cbegin(); child_node < children.cend(); child_node++)
		{
			int score = minimax(*child_node, depth - 1, player ^ 1);
			if (score < best_score)
			{
				if (depth == max_depth)
					best_move = child_node->move;
				best_score = score;
			}
		}
		return best_score;
	}
}

int		Engine::minimax_abp(Node node, int depth, int alpha, int beta, uint8_t player)
{
	if (depth == 0 || node.board.is_endgame(node.move, player, rule == Restricted))
		return node.score;

	if (player + 1 == Black)
	{
		int	best_score = numeric_limits<int>::min();
		auto children = generate_children(node.board, player);
		sort_children(children, player);
		for (auto child_node = children.cbegin(); child_node < children.cend(); child_node++)
		{
			int score = minimax_abp(*child_node, depth - 1, alpha, beta, player ^ 1);
			if (score > best_score)
			{
				if (depth == max_depth)
					best_move = child_node->move;
				best_score = score;
				if (score > alpha)
					alpha = score;
				if (alpha >= beta)
					break;
			}
		}
		return best_score;
	}
	else
	{
		int	best_score = numeric_limits<int>::max();
		auto children = generate_children(node.board, player);
		sort_children(children, player);
		for (auto child_node = children.cbegin(); child_node < children.cend(); child_node++)
		{
			int score = minimax_abp(*child_node, depth - 1, alpha, beta, player ^ 1);
			if (score < best_score)
			{
				if (depth == max_depth)
					best_move = child_node->move;
				best_score = score;
				if (score < beta)
					beta = score;
				if (alpha >= beta)
					break;
			}
		}
		return best_score;
	}
}

size_t	Engine::get_best_move(Board board, uint8_t player, Algorithm algo)
{
	auto best_score = 0;

	if (board.indexes[0].size() == 0 && board.indexes[1].size() == 0)
		return BOARD_CAPACITY / 2;
	best_move = 0;
	nb_eval = 0;
	auto start_node = Node { board, 0, 0 };
	if (algo == Minimax)
		best_score = minimax(start_node, max_depth, player);
	else if (algo == MinimaxWithPruning)
		best_score = minimax_abp(start_node, max_depth, numeric_limits<int>::min(), numeric_limits<int>::max(), player);
	else if (algo == Negamax)
		best_score = negamax(start_node, max_depth, player);
	else if (algo == NegamaxWithPruning)
		best_score = negamax_abp(start_node, max_depth, numeric_limits<int>::min(), numeric_limits<int>::max(), player);
	else
		best_score = pvs(start_node, max_depth, numeric_limits<int>::min(), numeric_limits<int>::max(), player);
	printf("number of call to eval function: %d\n", nb_eval);
	printf("best score for position: %d\n", best_score);
	return best_move;
}