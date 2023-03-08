#include "bnf/grammar.h"

using namespace std;

void ProductionRule::getCardinality(big_int& cardinality, unsigned int totaln, unsigned int n, unsigned int ntpos) const {

    if (ntpos == nonTerminals.size()) {
        cardinality = (n == 0) ? 1 : 0;
    }

    else {

        const NonTerminal& nonTerminal = *nonTerminals[ntpos];

        big_int nonTerminalCard;
        big_int nextNonTerminalsCard;

        cardinality = 0;

        unsigned int minLength = nonTerminal.getMinLength();
        unsigned int maxLength = getSymbolMaxLength(n, totaln, minLength);

        for (unsigned int i = minLength; i <= maxLength; i++) {

            nonTerminal.getCardinality(nonTerminalCard, i);

            if (nonTerminalCard != 0) {
                getCardinality(nextNonTerminalsCard, totaln, n - i, ntpos + 1);
                cardinality += nonTerminalCard * nextNonTerminalsCard;
            }
        }
        
    }
}

void ProductionRule::getCardinality(big_int& cardinality, unsigned int n) const {
    return getCardinality(cardinality, n, n - terminalsLength, 0);
}

void Terminal::getCardinality(big_int& res, unsigned int n) const {
    res = (n == value.length()) ? 1 : 0;
}

void NonTerminal::getCardinality(big_int& cardinality, unsigned int n) const {

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

big_int NonTerminal::getCardinality(unsigned int n) const {
    big_int cardinality;
    getCardinality(cardinality, n);
    return cardinality;
}