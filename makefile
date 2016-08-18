
all:
	clang++ bf.cpp -o bf -std=c++11 -Wall -Wpedantic

debug:
	clang++ bf.cpp -o bf_debug -std=c++11 -Wall -Wpedantic -DDEBUG -lncurses

run: all
	./bf progs/helloworld.b

clean:
	rm bf bf_debug
