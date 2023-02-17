CXX = g++
CXXFLAGS = -lgmp -lgmpxx -Wall
# DEBUG = -g
# OPT = -O2

main: main.cpp build/grammar.o build/print.o build/parser.o build/lexer.o \
      build/valuation.o build/cardinality.o build/elements.o build/random.o
	$(CXX) $^ $(CXXFLAGS) $(OPT) $(DEBUG) -o $@

exec: main
	./main

debug: main
	gdb ./main

build/%.o: %.cpp grammar.h
	$(CXX) $< $(OPT) $(DEBUG) -c -o $@

clean:
	rm -rf main build/*