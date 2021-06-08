#include "bitwriter.h"

bitwriter::bitwriter(std::string file) : buff_size(8), counter(0) {
	out_file.open(file, std::ios::binary);
}

bitwriter::~bitwriter() {
	flush();
	out_file.close();
}

void bitwriter::flush() {
	out_file.write((const char*)&(buffer[0]), buffer.size());
	buffer.clear();
	counter = 0;
}

void bitwriter::set_bit(int index, int value) {
	buffer[index / sizeof(char) / 8] |= (value & 1) << 7 - (index & 7);
}

void bitwriter::write_bit(int value) {	
	if (counter == buffer.size() * 8)
		buffer.push_back(0);
	set_bit(counter, value);
	counter++;
	if (counter == buff_size * sizeof(char) * 8)
		flush();
}

void bitwriter::write(std::string s) {
	for (unsigned int i = 0; i < s.size(); i++)
		write_bit(std::stoi(std::string(1, s[i])));
}
