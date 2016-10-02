#include "conversion/uleb128.hpp"

uint64_t uleb128_from_istream(std::istream& stream)
{
	unsigned int shift = 0;
	uint64_t result = 0;
	char byte;

	while (stream.read(&byte, 1))
	{
		if (!stream)
			return 0;

		result |= (static_cast<uint64_t>(byte & 0x7f) << shift);
		if ((byte & 0x80) == 0)
			break;
		shift += 7;
	}

	return result;
}