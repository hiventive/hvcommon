#include <bitvector.h>
#include <iostream>

using namespace ::hv::common;

int sc_main(int argc, char* argv[]) {
	BitVector z(32, 0xF0F0F0F0);
	std::cout << z << std::endl;
	return 0;
}
