CXX = g++
CXXFLAGS = -Iinclude -lgmp -lgmpxx # -Wall
# DEBUG = -g
OPT = -O2

bin/main: src/main.cpp bin/grammar.o bin/print.o bin/parser.o bin/lexer.o \
          bin/valuation.o bin/cardinality.o bin/elements.o bin/random.o bin/element.o
	$(CXX) $^ $(CXXFLAGS) $(OPT) $(DEBUG) -o $@

exec: bin/main
	./bin/main

debug: bin/main
	gdb ./bin/main

bin/%.o: src/%.cpp include/grammar.h
	@mkdir -p bin
	$(CXX) $< $(CXXFLAGS) $(OPT) $(DEBUG) -c -o $@

clean:
	rm -rf bin/*