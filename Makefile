CXX = g++
CXXFLAGS = -Iinclude -lgmp -lgmpxx # -Wall
# DEBUG = -g
OPT = -O2

OBJECTS = bin/grammar.o bin/print.o bin/parser.o bin/lexer.o bin/big_int.o \
          bin/valuation.o bin/cardinality.o bin/exists.o bin/elements.o \
		  bin/urandom.o bin/nurandom.o bin/element.o

TARGETS = bnf bnf.o cbnf.so tests

all: $(TARGETS)

bin/%.o: src/%.cpp include/bnf/grammar.h
	@mkdir -p bin
	$(CXX) $< $(CXXFLAGS) -fPIC $(OPT) $(DEBUG) -c -o $@

bnf: src/bnf.cpp $(OBJECTS)
	$(CXX) $(OPT) $^ $(CXXFLAGS) $(DEBUG) -o $@

bnf.o: $(OBJECTS)
	ld -r $(OBJECTS) -o $@

cbnf.so: src/cbnf.cpp $(OBJECTS)
	$(CXX) -fPIC -shared -fvisibility=hidden -o $@ $^ $(CXXFLAGS) $(OPT) $(DEBUG)

tests: src/tests.cpp $(OBJECTS)
	$(CXX) $^ $(CXXFLAGS) $(OPT) $(DEBUG) -o $@

test: tests
	./tests

doc.md: include/bnf/grammar.h
	mdoc doc.md include/bnf/grammar.h

test_python:
	python3 python/test.py

clean:
	rm -rf $(TARGETS) bin/* python/__pycache__