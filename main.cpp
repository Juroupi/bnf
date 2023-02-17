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

void printElement(Grammar& g, const string& nonTerminalName, int n, big_int&& id) {
    string element;
    auto start = std::chrono::high_resolution_clock::now();
    g.getElement(element, nonTerminalName, n, id);
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - start;
    cout << "element(\"" << nonTerminalName << "\", " << n << ", " << id << ") = '"
         << element << "'" << endl;
    printf("time = %fs\n", time.count());
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
    string random;
    g.getRandomElement(random, nonTerminalName, n);
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - start;
    cout << "random(\"" << nonTerminalName << "\", " << n << ") = '" << random << "'" << endl;
    printf("time = %fs\n", time.count());
}

void printRandomCount(Grammar& g, const string& nonTerminalName, int n, int total) {
    string random;
    map<string, int> count;
    for (int i = 0; i < total; i++) {
        g.getRandomElement(random, nonTerminalName, n);
        count[random]++;
        random.clear();
    }
    cout << "elements(\"" << nonTerminalName << "\", " << n << ") = [";
    for (auto& it : count) {
        if (&it != &(*count.begin())) cout << ",";
        cout << endl << "    \"" << it.first << "\" : " << it.second / (double)total;
    }
    cout << endl << "]" << endl;
}

int main() {

    Grammar g("data/fibo.bnf");

    g.print(true);

    // printCardinality(g, "F", 10000);

    return 0;
}