#include "grammar.h"

#include <iostream>

using namespace std;

big_int ProductionRule::getCardinality(int n, int pos) const {

    if (pos == nonTerminals.size()) {

        if (n == terminalsLength) {
            return 1;
        }

        return 0;
    }

    else {

        big_int card = 0;

        for (int i = 0; i <= n - terminalsLength; i++) {

            big_int nonTerminalCard = nonTerminals[pos]->getCardinality(i);

            if (nonTerminalCard != 0) {
                card += nonTerminalCard * getCardinality(n - i, pos + 1);
            }
        }

        return card;
    }
}

big_int NonTerminal::getCardinality(int n) {

    if (n < 0) {
        return 0;
    }

    if (n >= cardinalities.size()) {
        cardinalities.resize(n + 1);
    }

    if (cardinalities[n].first) {
        return cardinalities[n].second;
    }
    
    big_int card = 0;

    for (const ProductionRule& productionRule : productionRules) {
        card += productionRule.getCardinality(n);
    }

    cardinalities[n].first = true;
    cardinalities[n].second = card;

    return card;
}

big_int Grammar::getCardinality(const string& nonTerminalName, int n) {

    NonTerminal* nonTerminal = getNonTerminal(nonTerminalName, NULL);

    if (nonTerminal == NULL) {
        return 0;
    }

    return nonTerminal->getCardinality(n);
}