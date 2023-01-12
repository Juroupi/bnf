#include <iostream>

#include "grammar.h"

using namespace std;

void printCardinality(Grammar& g, const string& nonTerminalName, int n) {
    auto card = g.getCardinality(nonTerminalName, n);
    cout << "g.cardinality(\"" << nonTerminalName << "\", " << n << ") = " << card << endl;
}

int main() {

    Grammar g("data/fibo.bnf");

    printCardinality(g, "F", 1000);

    return 0;
}