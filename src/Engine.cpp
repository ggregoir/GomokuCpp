#include "Engine.h"
#include <algorithm>

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

	restricted_mode = rule == Restricted;
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
					if (restricted_mode && seq.len == 2 && seq.blocked == 1)
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