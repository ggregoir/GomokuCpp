#include "Board.h"

using namespace std;

Board::Board()
{
	for (int i = 0; i < BOARD_CAPACITY; i++) bit_board[i] = 0;
}

Board::~Board() {}

uint8_t		Board::operator[](uint32_t index)
{
	return (bit_board[index * 2 / 8] >> (index * 2 % 8)) & 0B11;
}

void		Board::update(uint32_t index, uint8_t value)
{
	auto bit_index = index * 2 / 8;
	auto offset = index * 2 % 8;

	// clearing bit pair
	bit_board[bit_index] &= ~(0B11 << offset);
	// setting bit pair to value
	bit_board[bit_index] |= value << offset;
}