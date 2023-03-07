#include <iostream>
#include <chrono>

#include "grammar.h"

using namespace std;

void printCardinality(NonTerminal& nonTerminal, unsigned int n) {

    auto start = std::chrono::high_resolution_clock::now();
    big_int card = nonTerminal.getCardinality(n);
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - start;

    cout << "cardinality(\"" << nonTerminal.getValue(true) << "\", " << n << ") = " << card << endl;

    printf("time = %fs\n", time.count());
}

void printElement(NonTerminal& nonTerminal, unsigned int n, big_int&& id) {

    cout << "element(\"" << nonTerminal.getValue(true) << "\", " << n << ", " << id << ") = ";

    auto start = std::chrono::high_resolution_clock::now();
    string element = nonTerminal.getElement(n, id);
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - start;

    cout << "'" << element << "'" << endl;

    printf("time = %fs\n", time.count());
}

void printElements(NonTerminal& nonTerminal, unsigned int n) {

    auto start = std::chrono::high_resolution_clock::now();
    set<string> elements = nonTerminal.getElements(n);
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - start;

    cout << "elements(\"" << nonTerminal.getValue(true) << "\", " << n << ") = [";
    for (const string& element : elements) {
        if (&element != &(*elements.begin())) cout << ",";
        cout << " \"" << element << "\"";
    }
    cout << " ]" << endl;

    printf("time = %fs\n", time.count());
}

void printRandom(NonTerminal& nonTerminal, unsigned int n) {

    auto start = std::chrono::high_resolution_clock::now();
    string random = nonTerminal.getRandomElement(n);
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - start;

    cout << "random(\"" << nonTerminal.getValue(true) << "\", " << n << ") = '" << random << "'" << endl;
    
    printf("time = %fs\n", time.count());
}

void printRandomCount(NonTerminal& nonTerminal, unsigned int n, unsigned int total) {

    map<string, unsigned int> count;

    for (unsigned int i = 0; i < total; i++) {
        string random = nonTerminal.getRandomElement(n);
        count[random]++;
        random.clear();
    }

    cout << "elements(\"" << nonTerminal.getValue(true) << "\", " << n << ") = [";

    for (auto& it : count) {
        if (&it != &(*count.begin())) cout << ",";
        cout << endl << "    \"" << it.first << "\" : " << it.second / (double)total;
    }

    cout << endl << "]" << endl;
}

int main() {

    Grammar g("data/par.bnf");

    for (unsigned int i = 0; i < 5; i++) {
        printElement(g["W"], 6, i);
    }

    return 0;
}