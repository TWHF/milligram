#ifndef __BITWRITER_H__
#define __BITWRITER_H__

#include <vector>
#include <fstream>

class bitwriter {
  public:
    bitwriter(std::string); //(filename)
    ~bitwriter();
    void flush();
    // write binary string to output file
    void write(std::string);

  private:
    std::vector<char> buffer;
    std::ofstream out_file;
    size_t buff_size; // buffer size
    size_t counter; // number of bits written
    // (index, value) , set value at index
    void set_bit(int,int);
    void write_bit(int); //value of bit to set
};

#endif
