#pragma once

#include <cstdint>

class Index
{
    public:

	    int		byte;
	    uint8_t	offset;

        Index();
        Index(int new_byte, uint8_t new_offset);
        ~Index();
        void    increment();
};