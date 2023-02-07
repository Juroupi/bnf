#include "grammar.h"

#include <climits>

using namespace std;

static int addLengths(int v1, int v2) {
    return min(Grammar::maxLength, v1 + v2);
}

static bool update(int& dst, int src) {

    if (dst == src) {
        return false;
    }

    dst = src;

    return true;
}

int ProductionRule::getMinLength() const {
    return minLength;
}

bool ProductionRule::updateMinLength() {

    int newMinLength = terminalsLength;

    for (const NonTerminal* nonTerminal : nonTerminals) {
        newMinLength = addLengths(nonTerminal->getMinLength(), newMinLength);
    }

    return update(minLength, newMinLength);
}

int NonTerminal::getMinLength() const {
    return minLength;
}

bool NonTerminal::updateMinLength() {
    
    int newMinLength = Grammar::maxLength;

    for (const ProductionRule& productionRule : productionRules) {
        newMinLength = min(productionRule.getMinLength(), newMinLength);
    }

    bool changes = update(minLength, newMinLength);

    for (ProductionRule& productionRule : productionRules) {
        changes = productionRule.updateMinLength() || changes;
    }

    return changes;
}

void Grammar::updateMinLength() {

    bool changes;

    do {

        changes = false;

        for (auto& it : nonTerminals) {
            changes = it.second.updateMinLength() || changes;
        }
    
    } while (changes);
}