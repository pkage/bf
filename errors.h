#ifndef BF_ERRORS
#define BF_ERRORS

#include <exception>

namespace bf {

	// publicly available errors
	namespace err {
		class ParseError : public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Parse error!";
				}
		} parse_error; // lazily init here

		// memory pointer has run off the left side of the memory
		class MemPointerOutOfBoundsError : public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Memory pointer out of bounds!";
				}
		} mem_pointer_out_of_bounds_error; // lazily init again :/

		// exec pointer has run off the left side of the memory
		class ExecPointerOutOfBoundsError : public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Execution pointer out of bounds!";
				}
		} exec_pointer_out_of_bounds_error; // lazily init again :/


		// could not load file
		class LoadError : public std::exception {
			public:
				virtual const char* what() const throw() {
					return "could not open file!";
				}
		} load_error; // lazily init here

	}
}

#endif

