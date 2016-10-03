#include "conversion/leb128.hpp"
#include "conversion/osustring.hpp"
#include <cassert>

std::string osustring_to_stdstring(unsigned char * buffer, unsigned char* end)
{
	assert(buffer[0] == 0x00 || buffer[0] == 0x0b && "osustring must start with either 00 or 0b.");

	if (buffer[0] == 0x00) return "";
	
	uint64_t string_size;
	auto size_read = read_uleb128_to_uint64(buffer + 1, end, &string_size);

	assert(size_read && "osustring_to_stdstring has reached EOF.");

	return std::string{ buffer + 1 + size_read, buffer + 1 + size_read + string_size };
}
