#include <iostream>
#include "encoder.h"

int main(int argc, char *argv[]) {

	if(argc < 1) {
		std::cout << "No filename given.\n";
		return 0;
	}

	std::string filename = argv[1];
	encode_img(filename, 2);

	return 0;
}
