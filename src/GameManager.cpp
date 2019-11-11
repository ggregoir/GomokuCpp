#include "GameManager.h"
#include "Position.h"

using namespace std;

GameManager::GameManager()
{
	turn = false;
}

GameManager::~GameManager() {}

bool		GameManager::modify_board(uint32_t new_index, Stone stone)
{
	if (board[new_index] != Empty)
		return false;
	board.update(new_index, stone);
	history.push_back(make_tuple(new_index, stone));
	return true;
}

uint32_t	GameManager::get_last_move()
{
	return get<0>(history.back());
}

Board		GameManager::get_board()
{
	return board;
}

void		GameManager::change_turn()
{
	turn = !turn;
}

Stone		GameManager::get_turn_color()
{
	return static_cast<Stone>(turn + 1);
}