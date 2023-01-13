#include <iostream>
#include <chrono>

#include "grammar.h"

using namespace std;

void printCardinality(Grammar& g, const string& nonTerminalName, int n) {
    auto start = std::chrono::high_resolution_clock::now();
    big_int card = g.getCardinality(nonTerminalName, n);
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - start;
    cout << "cardinality(\"" << nonTerminalName << "\", " << n << ") = " << card << endl;
    printf("temps = %fs\n", time.count());
}

int main() {

    Grammar g("data/fibo2.bnf");

    printCardinality(g, "F", 10000);

    return 0;
}