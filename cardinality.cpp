#include "grammar.h"

#include <iostream>

using namespace std;

static unsigned long long cardinality(
    const vector<NonTerminal*> nonTerminals,
    int terminalsLength,
    int n,
    int pos = 0
) {

    if (pos == nonTerminals.size()) {

        if (n == terminalsLength) {
            return 1;
        }

        return 0;
    }

    else {

        unsigned long long card = 0;

        for (int i = 0; i <= n - terminalsLength; i++) {

            unsigned long long nonTerminalCard = nonTerminals[pos]->getCardinality(i);

            if (nonTerminalCard != 0) {
                card += nonTerminalCard * cardinality(nonTerminals, terminalsLength, n - i, pos + 1);
            }
        }

        return card;
    }
}

unsigned long long ProductionRule::getCardinality(int n) const {
    return cardinality(nonTerminals, terminalsLength, n);
}

unsigned long long NonTerminal::getCardinality(int n) const {
    
    unsigned long long card = 0;

    for (const ProductionRule& productionRule : productionRules) {
        card += productionRule.getCardinality(n);
    }

    return card;
}

unsigned long long Grammar::getCardinality(const string& nonTerminalName, int n) const {

    const NonTerminal* nonTerminal = getNonTerminal(nonTerminalName);

    if (nonTerminal == NULL) {
        return 0;
    }

    return nonTerminal->getCardinality(n);
}