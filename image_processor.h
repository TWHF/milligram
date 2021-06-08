#ifndef __IMAGE_PROCESSOR_H__
#define __IMAGE_PROCESSOR_H__

const int IMG_LEN = 512;
const int BLK_LEN = 64;
/*
 * moved to .cpp file
bool IMG_LOADED = false;
int IMAGE[IMG_LEN][IMG_LEN];
*/

// load .pbm image into a 2d array passed as an argument
void load_img(std::string);

// would return the constant BLK_LEN;
int get_blk_size();
// would return the constant IMG_LEN;
int get_img_size();

// (left, top, size), return count of black pixels in the region
int get_count_bp(int,int,int);
// (size), return count of total pixels(size^2);
int get_count_tp(int);

#endif
