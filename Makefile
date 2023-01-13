CXX = g++
CXXFLAGS = -O2 -lgmp -lgmpxx

main: main.cpp build/grammar.o build/print.o build/parser.o build/lexer.o build/cardinality.o
	$(CXX) $^ $(CXXFLAGS) -o $@

exec: main
	./main

build/grammar.o: grammar.cpp grammar.h
	$(CXX) $< -c -o $@

build/print.o: print.cpp grammar.h
	$(CXX) $< -c -o $@

build/parser.o: parser.cpp grammar.h
	$(CXX) $< -c -o $@

build/lexer.o: lexer.cpp lexer.h
	$(CXX) $< -c -o $@

build/cardinality.o: cardinality.cpp grammar.h
	$(CXX) $< -c -o $@

clean:
	rm -rf main build/*