#include "grammar.h"

#include <iostream>

using namespace std;

void ProductionRule::getCardinality(big_int& card, int n, int pos) const {

    if (pos == nonTerminals.size()) {
        card = (n == terminalsLength) ? 1 : 0;
    }

    else {

        card = 0;

        big_int nonTerminalCard;
        big_int nextNonTerminalsCard;

        for (int i = 0; i <= n - terminalsLength; i++) {
            
            nonTerminals[pos]->getCardinality(nonTerminalCard, i);

            if (nonTerminalCard != 0) {
                getCardinality(nextNonTerminalsCard, n - i, pos + 1);
                card += nonTerminalCard * nextNonTerminalsCard;
            }
        }

    }
}

void NonTerminal::getCardinality(big_int& card, int n) {

    if (n < 0) {
        card = 0;
        return;
    }

    if (n >= cardinalities.size()) {
        cardinalities.resize(n + 1, NULL);
    }

    if (cardinalities[n] != NULL) {
        card = *cardinalities[n];
        return;
    }
    
    card = 0;

    big_int productionRuleCard;

    for (const ProductionRule& productionRule : productionRules) {
        productionRule.getCardinality(productionRuleCard, n);
        card += productionRuleCard;
    }

    cardinalities[n] = new big_int(card);
}

big_int NonTerminal::getCardinality(int n) {
    big_int card;
    getCardinality(card, n);
    return card;
}

void Grammar::getCardinality(big_int& card, const string& nonTerminalName, int n) {

    NonTerminal* nonTerminal = getNonTerminal(nonTerminalName, NULL);

    if (nonTerminal == NULL) {
        card = 0;
        return;
    }

    nonTerminal->getCardinality(card, n);
}

big_int Grammar::getCardinality(const string& nonTerminalName, int n) {
    big_int card;
    getCardinality(card, nonTerminalName, n);
    return card;
}