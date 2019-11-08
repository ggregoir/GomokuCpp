#include "GameManager.h"

#include <string.h>
#include <tuple>
#include <iostream>

using namespace std;

GameManager::Board::Board()
{
	for (int i = 0; i < BOARD_CAPACITY; i++) board[i] = 0;
}

GameManager:::Board::~Board() {}

GameManager::GameManager()
{
	turn = false;
}

GameManager::~GameManager() {}

bool		GameManager::modify_board(uint32_t new_index, Stone stone)
{
	if (board[new_index] != Empty)
		return false;
	board[new_index] = stone;
	history.push_back(make_tuple(new_index, stone));
	return true;
}

uint32_t	GameManager::get_last_move()
{
	return get<0>(history.back());
}

board_t		GameManager::get_board()
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