#include "grammar.h"

using namespace std;

static inline void prefixSum(vector<big_int>& values) {
    for (int i = 1; i < values.size(); i++) {
        values[i] += values[i - 1];
    }
}

static inline int weightedRandomChoice(rand_state& randState, const vector<big_int>& weightSums) {

    big_int random = randState.get_z_range(weightSums.back());

    for (int i = 0; i < weightSums.size(); i++) {

        if (weightSums[i] < random) {
            return i;
        }
    }

    return weightSums.size() - 1;
}

void ProductionRule::getRandomElement(string& element, int n, rand_state& randState, int pos) {
    
}

void NonTerminal::getRandomElement(string& element, int n, rand_state& randState) {

    vector<big_int> cardinalities(productionRules.size());

    for (int i = 0; i < cardinalities.size(); i++) {
        getCardinality(cardinalities[i], n);
    }

    prefixSum(cardinalities);

    int choice = weightedRandomChoice(randState, cardinalities);

    productionRules[choice].getRandomElement(element, n, randState);
}

void NonTerminal::getRandomElement(string& element, int n) {
    rand_state randState(gmp_randinit_mt);
    getRandomElement(element, n, randState);
}

void Grammar::getRandomElement(string& element, const string& nonTerminalName, int n) {

    NonTerminal* nonTerminal = getNonTerminal(nonTerminalName, NULL);

    if (nonTerminal != NULL) {
        nonTerminal->getRandomElement(element, n);
    }
}

string Grammar::getRandomElement(const string& nonTerminalName, int n) {
    string element;
    getRandomElement(element, nonTerminalName, n);
    return element;
}