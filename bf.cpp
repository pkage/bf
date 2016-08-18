/**
 * Naive first pass at a brainfuck interpreter
 * @author Patrick Kage (@quadnix)
 */
#include <iostream>
#include <fstream>

#include "parser.h"

using namespace std;

int main(int argc, char** argv) {

	if (argc != 2) {
		cout << "usage: " << argv[0] << " [filename]\n";
		return 1;
	}

	bf::Parser parser;
	parser.load_from_file(argv[1]);


	do {
#ifdef DEBUG
		parser.dump_state(16);
#endif
	} while(parser.tick());

	

	return 0;
}
