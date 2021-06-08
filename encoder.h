#ifndef __ENCODER_H__
#define __ENCODER_H__

class node {
  public:
  std::string index; //Z-order index
  int size; //length of node(in power of 2);
  int left, top; // left, top coordinates
  node();
  node(int,int,int);
  void change_loc(int,int,int);
  void append_index(std::string);
};

void init_img(std::string);

void encode_img(std::string, int); //(filename, thresh)
void encode_blk(int,int,int); //(left,top,thresh)

// (b.index, size)
std::string get_opcode(const std::string&, int);
// return morton code in binary
std::string get_md_code(const std::string&);
// (num, len) binary code of size len for num
std::string get_binary_code(int,int);

#endif
