#include <iostream>

#include "grammar.h"

using namespace std;

void printCardinality(Grammar& g, const string& nonTerminalName, int n) {
    auto card = g.getCardinality(nonTerminalName, n);
    cout << "g.cardinality(\"" << nonTerminalName << "\", " << n << ") = " << card << endl;
}

int main() {

    Grammar g("data/par.bnf");

    for (int i = 0; i < 10; i++) {
        printCardinality(g, "W", i);
    }

    return 0;
}