#include "GameManager.h"

#include <string.h>
#include <tuple>
#include <iostream>

using namespace std;

GameManager::GameManager()
{
	turn = false;
	if (params.get_priority())
		player = true;
	else
		player = false;
	for (int i = 0; i < BOARD_CAPACITY; i++) board[i] = 0;
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

Board		GameManager::get_board()
{
	return board;
}

void		GameManager::change_turn()
{
	turn = !turn;
}

void		GameManager::change_player()
{
	if (params.get_mode() != PlayerVsPlayer && params.get_mode() != EngineVsEngine)
		player = !player;
}

uint8_t		GameManager::get_turn_color()
{
	return (uint8_t)turn;
}