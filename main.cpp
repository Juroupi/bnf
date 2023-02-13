#include <iostream>
#include <chrono>

#include "grammar.h"

using namespace std;

void printCardinality(Grammar& g, const string& nonTerminalName, int n) {
    auto start = std::chrono::high_resolution_clock::now();
    big_int card = g.getCardinality(nonTerminalName, n);
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - start;
    cout << "cardinality(\"" << nonTerminalName << "\", " << n << ") = " << card << endl;
    printf("time = %fs\n", time.count());
}

void printCardinalityCSV(Grammar& g, const string& nonTerminalName, int n) {
    auto start = std::chrono::high_resolution_clock::now();
    big_int card = g.getCardinality(nonTerminalName, n);
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - start;
    printf("%d,%f\n", n, time.count());
}

void printElements(Grammar& g, const string& nonTerminalName, int n) {
    set<string> elements;
    auto start = std::chrono::high_resolution_clock::now();
    g.getElements(elements, nonTerminalName, n);
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - start;
    cout << "elements(\"" << nonTerminalName << "\", " << n << ") = [";
    for (const string& element : elements) {
        if (&element != &(*elements.begin())) cout << ",";
        cout << " \"" << element << "\"";
    }
    cout << " ]" << endl;
    printf("time = %fs\n", time.count());
}

void printRandom(Grammar& g, const string& nonTerminalName, int n) {
    auto start = std::chrono::high_resolution_clock::now();
    string random = g.getRandomElement(nonTerminalName, n);
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - start;
    cout << "random(\"" << nonTerminalName << "\", " << n << ") = '" << random << "'" << endl;
    printf("time = %fs\n", time.count());
}

int main() {

    Grammar g("data/uni.bnf");

    // g.print(true);

    printRandom(g, "S", 1);

    return 0;
}