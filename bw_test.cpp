#include <iostream>
#include "bitwriter.h"
using namespace std;

int main() {
	bitwriter bw("t.out");
	bw.write("11100011100011001100");
	return 0;
}
