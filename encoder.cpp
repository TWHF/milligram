#include <iostream>
#include <stack>
#include "encoder.h"
#include "bitwriter.h"
#include "image_processor.h"
using namespace std;

stack<string> OPCODES;

node::node() {}

node::node(int l, int t, int s) {
  size = s;
  left = l;
  top = t;
  index = "";
}

void node::change_loc(int newl, int newt, int news) {
  left = newl;
  top = newt;
  size = news;
}

void node::append_index(string c) {
  index += c;
}

void init_img(string filename) {
  load_img(filename);
}

// binary code of size len for num
string get_binary_code(int num, int len) {
  string c="";
  for(int i = len-1; i >= 0; i--) {
    if(num & (1 << i)) {
      c += "1";
    } else {
      c += "0";
    }
  }
  return c;
}

string get_md_code(const string & index) {
  string c="";
  for(auto i : index) {
    switch(i) {
      case '0':
        c += "00";
        break;
      case '1':
        c += "01";
        break;
      case '2':
        c += "10";
        break;
      case '3':
        c += "11";
        break;
    }
  }
  return c;
}

string get_opcode(const string & index, int node_size) {
  // prepare opcode
  // 1. 3bits for length of b.index as |b.index| < 7
  string opcode = get_binary_code(index.size(), 3);

  // 2. b.index in the binary notation
  opcode += get_md_code(index);

  // 3. 7bits for size in binary, |size| < 8
  opcode += get_binary_code(node_size, 7);
  
  return opcode;
}

void encode_blk(int left, int top, int thresh) {

  int size = get_blk_size();
  int bp = get_count_bp(left, top, size);

  if(bp == 0) {
    // whole block is white
    return;
  }
  if(get_count_tp(size) == bp) {
    // whole block is black
    // get opcode for md index 0(top left) and size of whole block
    OPCODES.push(get_opcode("0", size));
    return;
  }

  stack<node> S;

  size >>= 1; // size halved for subdivision coordinates calculation
  node b[4];
  int dl[4] = {0,1,0,1};
  int dt[4] = {0,0,1,1};
  string idx[4] = {"0","1","2","3"};

  for(int i = 0; i < 4; i++) {
    // push initial 4 nodes in S
    b[i] = node(left + dl[i] * size, top + dt[i] * size, size);
    b[i].append_index(idx[i]);
    S.push(b[i]);
  }

  node n;
  while(!S.empty()) {
    n = S.top(); S.pop();
    size = n.size;
    bp = get_count_bp(n.left, n.top, size); 

    //printf("Node size %d at (%d,%d) bp=%d\n", size, n.left, n.top, bp);

    // size == thresh
    if(size == thresh) {

      // if black is atleast in half of the pixels, we encode this node
      if(2 * bp >= get_count_tp(size)) {
        // push opcode for node in T
        OPCODES.push(get_opcode(n.index, size));
      } // else white, do nothing

    } else {
    // size > thresh

      // node is white, do nothing
      if(bp == 0) continue;
  
      if(bp == get_count_tp(size)) {
        // push opcode for node in T
        OPCODES.push(get_opcode(n.index, size));
      } else {
        // threshold is still not reached
        // we subdivide the node and push all of them in S
        size >>= 1;
        for(int i=0; i < 4; i++) {
          b[i] = n;
          b[i].change_loc(n.left + dl[i] * size, n.top + dt[i] * size, size);
          b[i].append_index(idx[i]);
          S.push(b[i]);
        }
      }
    }
  }
}

void encode_img(string filename, int thresh) {
  //load image to a 2d array
  load_img(filename + ".pbm");

  // create bitwriter with filename
  bitwriter bw(filename + ".out");

  // for each block in the image`
  int img_size = get_img_size();
  int blk_size = get_blk_size();
  string c;

  // encode it using quadtree and add the bitsream to bitwriter
  for(int top = 0; top < img_size; top += blk_size) {
    for(int left = 0; left < img_size; left += blk_size) {
      // block is encoded by passing coordinates in raster scan order
      encode_blk(left, top, thresh);

      // OPCODES now have values that are to be placed on bitstream
      while(!OPCODES.empty()) {
        c = OPCODES.top(); OPCODES.pop();
        //cout << c << "\n";
        bw.write(c);
      }
      bw.write("000");
      // OPCODES is now emptied so that next block can use it
    }
  }

  bw.flush();
  // print success alert
  cout << "Successfully encoded to " << filename << ".out\n";
}
