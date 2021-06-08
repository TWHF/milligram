#include <iostream>
#include <fstream>
#include "image_processor.h"

bool IMG_LOADED = false;
int IMAGE[IMG_LEN][IMG_LEN];

int get_blk_size() {return BLK_LEN;}
int get_img_size() {return IMG_LEN;}

int get_count_tp(int size) {return size * size;}

int get_count_bp(int left, int top, int size) {
	if(!IMG_LOADED) return -1;

	int count = 0;
	for(int i = top; i < top + size; i++) {
		for(int j = left; j < left + size; j++) {
			count += IMAGE[i][j];
		}
	}
	return count;
}

void load_img(std::string filename) {
	std::ifstream fin;
	fin.open(filename);

	std::string type;
	int width, height;
	fin >> type;
	fin >> width >> height;

	if(width > IMG_LEN or height > IMG_LEN) return;

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			fin >> IMAGE[i][j];
		}
	}
	IMG_LOADED = true;
}

