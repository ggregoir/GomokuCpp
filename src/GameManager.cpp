#include "GameManager.h"
#include "Position.h"

#include <string.h>
#include <tuple>
#include <iostream>

using namespace std;

GameManager::Board::Board()
{
	for (int i = 0; i < BOARD_CAPACITY; i++) bit_board[i] = 0;
}

GameManager::Board::~Board() {}

uint8_t		GameManager::Board::operator[](uint32_t index)
{
	return (bit_board[index * 2 / 8] >> (index * 2 % 8)) & 0B11;
}

void		GameManager::Board::update(uint32_t index, uint8_t value)
{
	auto bit_index = index * 2 / 8;
	auto n = index * 2 & 8;
	// clearing bit pair
	bit_board[bit_index] &= ~(0B11 << n);
	// setting bit pair to value
	bit_board[bit_index] |= value << n;
}

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

GameManager::Board		GameManager::get_board()
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