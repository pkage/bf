#ifndef BF_PARSER
#define BF_PARSER

#include <string>
#include <stack>
#include <fstream>
#include <iostream>

#include "errors.h"
#include "memory.h"

namespace bf {
	// Parser class, coordinates everything else
	class Parser {
		private:
			std::string program;
			int exec_ptr;
			std::stack<int> loops;
			Memory mem;
		public:
#ifdef DEBUG
			// true if we want to freeze after this tick
			bool bpoint = false;
#endif
			Parser() {
				exec_ptr = 0;
				program = "";
			}

			// stringify the vm state
			void dump_state(int mem_length) {
				
				std::cout << exec_ptr << "\t\"" << program[exec_ptr] << "\"\t";
				mem.get_rep_for(mem_length);
				std::cout << "\r";
			}


			bool load_from_file(std::string fn) {
				std::ifstream ifile;

				// load the file
				ifile.open(fn);

				if (!ifile) {
					ifile.close();
					throw err::load_error;
				}

				std::string line, program = "";
				while (!ifile.eof()) {
					std::getline(ifile, line);
					program += line;
				}

				ifile.close();
				this->program = program;

				return 0;
			}

			bool is_done() {
				// not done until we've finished the last op
				return (exec_ptr == program.size());
			}

			bool tick() {
				if (is_done()) return false;

				switch (program[exec_ptr]) {
					// basic memory manip
					case '<':
						mem.slide_left();
						break;
					case '>':
						mem.slide_right();
						break;
					case '+':
						mem.increment_pointer();
						break;
					case '-':
						mem.decrement_pointer();
						break;

						// io
					case '.':
						std::cout << mem.read();
						break;
					case ',':
						char c; std::cin >> c;
						mem.write(c);
						break;

						// loop implementations
					case '[': // open loop
						if (int(mem.read()) == 0) {
							// if mem at mem ptr is zero skip ahead
							int depth = 1, seek = exec_ptr;
							while (depth != 0) {
								seek++;

								if (seek == program.size()) throw err::exec_pointer_out_of_bounds_error;

								if (program[seek] == '[') depth++;
								if (program[seek] == ']') depth--;
							}

							exec_ptr = seek;
						} else {
							loops.push(exec_ptr);
						}

						break;

					case ']': // close loop
						if (loops.size() > 0) {
							exec_ptr = loops.top() - 1;
							loops.pop();
						} else throw err::parse_error;
						break;

#ifdef DEBUG
					case '#':
						bpoint = true;
#endif
					default:
						break;
				}

				exec_ptr++;
				return true;
			}
	};
}

#endif
