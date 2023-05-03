#include "bnf/grammar.h"

using namespace std;

static const big_int zero = 0;
static const big_int one = 1;

void ProductionRule::getCardinality(big_int& cardinality, unsigned int totaln, unsigned int n, unsigned int ntpos) const {

    if (ntpos == nonTerminals.size()) {
        cardinality = (n == 0) ? 1 : 0;
    }

    else {

        const NonTerminal& nonTerminal = *nonTerminals[ntpos];

        big_int nextNonTerminalsCard;

        cardinality = 0;

        unsigned int minLength = nonTerminal.getMinLength();
        unsigned int maxLength = getSymbolMaxLength(n, totaln, minLength);

        for (unsigned int i = minLength; i <= maxLength; i++) {

            const big_int& nonTerminalCard = nonTerminal.getCardinality(i);

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

const big_int& Terminal::getCardinality(unsigned int n) const {

    if (n == value.length()) {
        return one;
    }

    return zero;
}

const big_int& NonTerminal::getCardinality(unsigned int n) const {

    if (n >= cardinalities.size()) {
        cardinalities.resize(n + 1);
    }

    if (!cardinalities[n]) {
        
        big_int& cardinality = *(cardinalities[n] = make_unique<big_int>(0));

        big_int productionRuleCard;
        
        for (const ProductionRule& productionRule : productionRules) {
            
            if (n >= productionRule.getMinLength()) {
            
                productionRule.getCardinality(productionRuleCard, n);
                cardinality += productionRuleCard;
            }
        }
    }

    return *cardinalities[n];
}