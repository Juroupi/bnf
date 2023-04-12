#include "bnf/grammar.h"

using namespace std;

bool ProductionRule::getExists(unsigned int totaln, unsigned int n, unsigned int ntpos) const {

    if (ntpos >= nonTerminals.size()) {
        return n == 0;
    }

    const NonTerminal& nonTerminal = *nonTerminals[ntpos];

    unsigned int minLength = nonTerminal.getMinLength();
    unsigned int maxLength = getSymbolMaxLength(n, totaln, minLength);

    for (unsigned int i = minLength; i <= maxLength; i++) {

        if (nonTerminal.getExists(i) && getExists(totaln, n - i, ntpos + 1)) {
            return true;
        }
    }
    
    return false;
}

bool ProductionRule::getExists(unsigned int totaln, unsigned int n, unsigned int ntpos, vector<unsigned int> ntposes) const {

    if (ntpos >= nonTerminals.size()) {
        return n == 0;
    }

    const NonTerminal& nonTerminal = *nonTerminals[ntposes[ntpos]];

    unsigned int minLength = nonTerminal.getMinLength();
    unsigned int maxLength = getSymbolMaxLength(n, totaln, minLength);

    for (unsigned int i = minLength; i <= maxLength; i++) {

        if (nonTerminal.getExists(i) && getExists(totaln, n - i, ntpos + 1, ntposes)) {
            return true;
        }
    }
    
    return false;
}

bool ProductionRule::getExists(unsigned int n) const {
    return getExists(n, n - terminalsLength, 0);
}

bool Terminal::getExists(unsigned int n) const {
    return n == value.length();
}

bool NonTerminal::getExists(unsigned int n) const {

    if (n < 0) {
        return false;
    }

    if (n >= existences.size()) {
        existences.resize(n + 1);
    }

    if (existences[n].has_value()) {
        return *existences[n];
    }
    
    for (const ProductionRule& productionRule : productionRules) {

        if (n >= productionRule.getMinLength() && productionRule.getExists(n)) {
            return *(existences[n] = true);
        }
    }

    return *(existences[n] = false);
}