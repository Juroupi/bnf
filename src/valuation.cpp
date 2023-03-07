#include "grammar.h"

#include <climits>

using namespace std;

static unsigned int addLengths(unsigned int v1, unsigned int v2) {
    return min(Grammar::maxLength, v1 + v2);
}

static bool update(unsigned int& dst, unsigned int src) {

    if (dst == src) {
        return false;
    }

    dst = src;

    return true;
}

unsigned int ProductionRule::getMinLength() const {
    return minLength;
}

bool ProductionRule::updateMinLength() {

    unsigned int newMinLength = terminalsLength;

    for (const NonTerminal* nonTerminal : nonTerminals) {
        newMinLength = addLengths(nonTerminal->getMinLength(), newMinLength);
    }

    return update(minLength, newMinLength);
}

unsigned int Terminal::getMinLength() const {
    return value.length();
}

unsigned int NonTerminal::getMinLength() const {
    return minLength;
}

bool NonTerminal::updateMinLength() {
    
    unsigned int newMinLength = Grammar::maxLength;

    for (const ProductionRule& productionRule : productionRules) {
        newMinLength = min(productionRule.getMinLength(), newMinLength);
    }

    bool changes = update(minLength, newMinLength);

    for (ProductionRule& productionRule : productionRules) {
        changes = productionRule.updateMinLength() || changes;
    }

    return changes;
}

void Grammar::updateMinLengths() {

    bool changes;

    do {

        changes = false;

        for (auto& it : nonTerminals) {
            changes = it.second.updateMinLength() || changes;
        }
    
    } while (changes);
}