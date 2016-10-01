/*
	main header file needed to manipulate all custom types of osu data
*/

#pragma once

#include <cstdint>

#include "leb128.hpp"
#include "osustring.hpp"


inline uint64_t uleb128_to_uint64_t(unsigned char* uleb)
{
	uint64_t ret;
	read_uleb128_to_uint64(uleb, uleb + sizeof(uint64_t), &ret);
	return ret;
}

int64_t uleb128_to_int64_t(unsigned char* uleb)
{
	int64_t ret;
	read_sleb128_to_int64(uleb, uleb + sizeof(int64_t), &ret);
	return ret;
}