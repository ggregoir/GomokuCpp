#pragma once

#include <string>

class Position
{

	public:

		int	x;
		int	y;

		Position(int xval = 0, int yval = 0);
		~Position();

		uint32_t	index(void);

};