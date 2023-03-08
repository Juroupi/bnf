CXX = g++
CXXFLAGS = -Iinclude -lgmp -lgmpxx -fPIC -Wall
DEBUG = -g
OPT = -O2

OBJECTS = bin/grammar.o bin/print.o bin/parser.o bin/lexer.o bin/big_int.o \
          bin/valuation.o bin/cardinality.o bin/elements.o bin/random.o bin/element.o

all: bnf cbnf.so

bnf: src/bnf.cpp $(OBJECTS)
	$(CXX) $^ $(CXXFLAGS) $(OPT) $(DEBUG) -o $@

cbnf.so: src/cbnf.cpp $(OBJECTS)
	$(CXX) -shared -fvisibility=hidden -o $@ $^ $(CXXFLAGS) $(OPT) $(DEBUG)

bin/%.o: src/%.cpp include/grammar.h
	@mkdir -p bin
	$(CXX) $< $(CXXFLAGS) $(OPT) $(DEBUG) -c -o $@

clean:
	rm -rf bnf cbnf.so bin/* python/__pycache__