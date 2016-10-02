#pragma once

#include <istream>
#include <cstdint>

uint64_t uleb128_from_istream(std::istream& stream);