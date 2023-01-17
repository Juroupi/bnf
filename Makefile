CXX = g++
CXXFLAGS = -lgmp -lgmpxx
DEBUG = -g
# OPT = -O2

main: main.cpp build/grammar.o build/print.o build/parser.o build/lexer.o \
      build/cardinality.o build/elements.o build/random.o
	$(CXX) $^ $(CXXFLAGS) $(OPT) $(DEBUG) -o $@

exec: main
	./main

build/grammar.o: grammar.cpp grammar.h
	$(CXX) $< $(OPT) $(DEBUG) -c -o $@

build/print.o: print.cpp grammar.h
	$(CXX) $< $(OPT) $(DEBUG) -c -o $@

build/parser.o: parser.cpp grammar.h
	$(CXX) $< $(OPT) $(DEBUG) -c -o $@

build/lexer.o: lexer.cpp lexer.h
	$(CXX) $< $(OPT) $(DEBUG) -c -o $@

build/cardinality.o: cardinality.cpp grammar.h
	$(CXX) $< $(OPT) $(DEBUG) -c -o $@

build/random.o: random.cpp grammar.h
	$(CXX) $< $(OPT) $(DEBUG) -c -o $@

build/elements.o: elements.cpp grammar.h
	$(CXX) $< $(OPT) $(DEBUG) -c -o $@

clean:
	rm -rf main build/*