#include <iostream>

#include "grammar.h"

using namespace std;

void printCardinality(Grammar& g, const string& nonTerminalName, int n) {
    auto card = g.getCardinality(nonTerminalName, n);
    cout << "g.cardinality(\"" << nonTerminalName << "\", " << n << ") = " << card << endl;
}

int main() {

    Grammar g("data/fibo2.bnf");

    printCardinality(g, "F", 300);

    return 0;
}