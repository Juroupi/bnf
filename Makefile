main: main.cpp build/grammar.o build/print.o build/parser.o build/lexer.o build/cardinality.o
	g++ main.cpp \
		build/grammar.o build/print.o build/parser.o build/lexer.o build/cardinality.o \
		-lgmp -lgmpxx \
		-o main

exec: main
	./main

build/grammar.o: grammar.cpp grammar.h
	g++ grammar.cpp -c -o build/grammar.o

build/print.o: print.cpp grammar.h
	g++ print.cpp -c -o build/print.o

build/parser.o: parser.cpp grammar.h
	g++ parser.cpp -c -o build/parser.o

build/lexer.o: lexer.cpp lexer.h
	g++ lexer.cpp -c -o build/lexer.o

build/cardinality.o: cardinality.cpp grammar.h
	g++ cardinality.cpp -c -o build/cardinality.o

clean:
	rm -rf main build/*