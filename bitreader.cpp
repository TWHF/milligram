#include <algorithm>
#include <string.h>
#include "bitreader.hpp"

BitReader::BitReader(std::string file) : size(8) {
	in.open(file, std::ios::binary);
	buffer = (char*)malloc(size * sizeof(char));
	memset(buffer, 0, size);
}

BitReader::~BitReader() {
	in.close();
}

bool BitReader::getBit(int index) {
	return (buffer[index / sizeof(char) / 8] >> 7 - (index & 7)) & 1;
}

std::vector<bool> BitReader::read() {
	int count = size;
	if (!in.read(buffer, size))
		count = in.gcount();
	std::vector<bool> result(count * sizeof(char) * 8);
	std::generate(result.begin(), result.end(), [this, i = 0]() mutable {return getBit(i++);});
	return result;
}

bool BitReader::ready() {
	int state = in.tellg();
	in.seekg(0, in.end);
	bool res = state != in.tellg();
	in.seekg(state);
	return res;
}
