/*
	binding inspired by http://www.asawicki.info/news_1368_lzma_sdk_-_how_to_use.html
*/

#pragma once

#include <vector>

void lzma_decompress(std::vector<char> &outBuf, const std::vector<char> &inBuf);