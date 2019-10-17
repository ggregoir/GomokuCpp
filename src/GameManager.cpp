#include "GameManager.h"

#include <string.h>
#include <tuple>
#include <iostream>

using namespace std;

GameManager::GameManager()
{
	for (int i = 0; i < 361; i++) board[i] = 0;
	cout << "GameManager constructor" << endl;
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