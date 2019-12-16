#include "Position.h"
#include "macros.h"

Position::Position(int xval, int yval)
{
    x = xval;
    y = yval;
}

Position::~Position() {}

uint32_t    Position::index(void)
{
    return x + y * BOARD_SIZE;
}