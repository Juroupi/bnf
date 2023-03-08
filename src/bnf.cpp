#include <iostream>
#include <cstdlib>
#include <string>
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

void printElement(NonTerminal& nonTerminal, unsigned int n, big_int&& id) {

    cout << "element(\"" << nonTerminal.getValue(true) << "\", " << n << ", " << id << ") = ";

    auto start = std::chrono::high_resolution_clock::now();
    string element = nonTerminal.getElement(n, id);
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - start;

    cout << "\"" << element << "\"" << endl;

    printf("time = %fs\n", time.count());
}

void printRandom(NonTerminal& nonTerminal, unsigned int n) {

    auto start = std::chrono::high_resolution_clock::now();
    string random = nonTerminal.getRandomElement(n);
    std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - start;

    cout << "random(\"" << nonTerminal.getValue(true) << "\", " << n << ") = \"" << random << "\"" << endl;
    
    printf("time = %fs\n", time.count());
}

void printCount(NonTerminal& nonTerminal, unsigned int n, unsigned int total) {

    map<string, unsigned int> count;

    for (unsigned int i = 0; i < total; i++) {
        string random = nonTerminal.getRandomElement(n);
        count[random]++;
        random.clear();
    }

    cout << "count(\"" << nonTerminal.getValue(true) << "\", " << n << ") = [";

    for (auto& it : count) {
        if (&it != &(*count.begin())) cout << ",";
        printf("\n    \"%s\" : %u (%g%%)", it.first.data(), it.second, it.second / (double)total * 100);
    }

    cout << endl << "]" << endl;
}

void printUsage(char* argv[]) {
    cout << "usage: " << argv[0] << " <file> <non-terminal> <command>" << endl;
    cout << "commands: " << endl;
    cout << "    cardinality <n>  -- The number of elements of size n that can be generated by the given non-terminal" << endl;
    cout << "    elements <n>     -- All the elements of size n that can be generated by the given non-terminal" << endl;
    cout << "    element <n> <id> -- The id-th element of size n that can be generated by the given non-terminal" << endl;
    cout << "    random <n>       -- A random element of size n that can be generated by the given non-terminal" << endl;
    cout << "    count <n> <r>    -- For each element of size n that can be generated by the given non-terminal, the number of times it was generated for a total of r random elements" << endl;
    cout << "example: " << argv[0] << " data/par.bnf W cardinality 6" << endl;
}

string getStringArg(int argc, char* argv[], int n) {

    if (n >= argc) {
        printUsage(argv);
        exit(1);
    }

    return argv[n];
}

unsigned int getUIntArg(int argc, char* argv[], int n) {

    if (n >= argc) {
        printUsage(argv);
        exit(1);
    }

    char* endptr;
    unsigned int val = (unsigned int)strtoul(argv[n], &endptr, 10);
    
    if (*endptr != '\0') {
        printUsage(argv);
        exit(1);
    }

    return val;
}

int main(int argc, char* argv[]) {

    Grammar g(getStringArg(argc, argv, 1));
    NonTerminal& nonTerminal = g[getStringArg(argc, argv, 2)];

    string command = getStringArg(argc, argv, 3);

    if (command == "cardinality") {
        printCardinality(nonTerminal, getUIntArg(argc, argv, 4));
    }
    
    else if (command == "elements") {
        printElements(nonTerminal, getUIntArg(argc, argv, 4));
    }
    
    else if (command == "element") {
        printElement(nonTerminal, getUIntArg(argc, argv, 4), getUIntArg(argc, argv, 5));
    }
    
    else if (command == "random") {
        printRandom(nonTerminal, getUIntArg(argc, argv, 4));
    }
    
    else if (command == "count") {
        printCount(nonTerminal, getUIntArg(argc, argv, 4), getUIntArg(argc, argv, 5));
    }
    
    else {
        printUsage(argv);
        return 1;
    }

    return 0;
}