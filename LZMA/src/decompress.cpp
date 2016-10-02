#include <vector>

#include "LzmaDecompress.h"

#include "decompress.hpp"

//not efficient
void lzma_decompress(std::vector<char> &outBuf, const std::vector<char> &inBuf)
{
	assert(!inBuf.empty() && "inBuf is empty");
	uint32_t size;
	LzmaGetInfo(reinterpret_cast<const void*>(inBuf.data()), inBuf.size(), &size);
	outBuf.resize(size);

	auto res = LzmaDecompress(reinterpret_cast<const void*>(inBuf.data()), inBuf.size(), reinterpret_cast<void*>(outBuf.data()));
	assert(res == EFI_SUCCESS && "decompression failed");
}