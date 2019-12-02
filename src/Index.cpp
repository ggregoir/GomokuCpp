#include "Index.h"

Index::Index()
{
    byte = 0;
    offset = 0;
}

Index::Index(int new_byte, uint8_t new_offset)
{
    byte = new_byte;
    offset = new_offset;
}

Index::~Index() {}

void    Index::increment()
{
    offset += 2;
    if (offset >= 8)
    {
        byte++;
        offset = 0;
    }
}