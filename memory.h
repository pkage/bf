#ifndef BF_MEMORY
#define BF_MEMORY

#include <vector>
#include "errors.h"

namespace bf {
	// memory class, literally just an array of ints
	class Memory {
		private:
			// some privates
			std::vector<int> mem;
			int pointer = 0;

			// inflate memory to a certain size so we don't get a perf. hit later
			void inflate_memory(int size) {
				for (int c = 0; c < size; c++) {
					mem.push_back(0);
				}
			}
		public:
			Memory() {
				inflate_memory(30000);
			}
			Memory(int size) {
				inflate_memory(size);
			}


			// debug only
			int get_pointer() {return pointer;}
			void get_rep_for(int len) {
				for (int c = 0; c < len; c++) {
					std::cout << "[" << mem[c] << "]";
				}

				std::cout << "\t" << pointer;
			}

			// implement actions
			void slide_right() { // ">"
				// if the pointer is larger than the memory space, increase the memory size
				if (++pointer >= mem.size()) mem.push_back(0);
			}
			void slide_left() { // "<"
				// make sure the pointer doesn't escape
				if (--pointer < 0) throw err::mem_pointer_out_of_bounds_error;
			}
			void increment_pointer() { // "+"
				mem[pointer]++;
			}
			void decrement_pointer() { // "-"
				mem[pointer]--;
			}

			char read() { // "." : used to output a bit to stdout
				return char(mem[pointer]);
			}

			void write(char in) { // "," : read from stdin
				mem[pointer] = int(in);
			}

	};

}
#endif
