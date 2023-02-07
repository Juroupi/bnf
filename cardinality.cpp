#include "grammar.h"

#include <iostream>

using namespace std;

void ProductionRule::getCardinality(big_int& cardinality, int totaln, int n, int pos) const {

    if (pos == nonTerminals.size()) {
        cardinality = (n == terminalsLength) ? 1 : 0;
    }

    else {

        NonTerminal& nonTerminal = *nonTerminals[pos];

        big_int nonTerminalCard;
        big_int nextNonTerminalsCard;

        cardinality = 0;

        int minLength = nonTerminal.getMinLength();
        int maxLength = min(n, totaln - (getMinLength() - minLength));

        for (int i = minLength; i <= maxLength; i++) {

            nonTerminal.getCardinality(nonTerminalCard, i);

            if (nonTerminalCard != 0) {
                getCardinality(nextNonTerminalsCard, totaln, n - i, pos + 1);
                cardinality += nonTerminalCard * nextNonTerminalsCard;
            }
        }
        
    }
}

void ProductionRule::getCardinality(big_int& cardinality, int n) const {
    return getCardinality(cardinality, n, n, 0);
}

void NonTerminal::getCardinality(big_int& cardinality, int n) {

    if (n < 0) {
        cardinality = 0;
        return;
    }

    if (n >= cardinalities.size()) {
        cardinalities.resize(n + 1);
    }

    if (cardinalities[n]) {
        cardinality = *cardinalities[n];
        return;
    }
    
    cardinality = 0;

    big_int productionRuleCard;
    
    for (const ProductionRule& productionRule : productionRules) {
        
        if (n >= productionRule.getMinLength()) {
        
            productionRule.getCardinality(productionRuleCard, n);
            cardinality += productionRuleCard;
        }
    }

    cardinalities[n] = make_unique<big_int>(cardinality);
}

big_int NonTerminal::getCardinality(int n) {
    big_int cardinality;
    getCardinality(cardinality, n);
    return cardinality;
}

void Grammar::getCardinality(big_int& cardinality, const string& nonTerminalName, int n) {

    NonTerminal* nonTerminal = getNonTerminal(nonTerminalName, NULL);

    if (nonTerminal != NULL) {
        nonTerminal->getCardinality(cardinality, n);
    }

    else {
        cardinality = 0;
    }
}

big_int Grammar::getCardinality(const string& nonTerminalName, int n) {
    big_int cardinality;
    getCardinality(cardinality, nonTerminalName, n);
    return cardinality;
}