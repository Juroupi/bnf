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

int ProductionRule::getMaxLength() const {
    return maxLength;
}

bool ProductionRule::updateMinLength() {

    int newMinLength = terminalsLength;

    for (const NonTerminal* nonTerminal : nonTerminals) {
        newMinLength = addLengths(nonTerminal->getMinLength(), newMinLength);
    }

    return update(minLength, newMinLength);
}

bool ProductionRule::updateMaxLength() {

    int newMaxLength = terminalsLength;

    for (const NonTerminal* nonTerminal : nonTerminals) {
        newMaxLength = addLengths(nonTerminal->getMaxLength(), newMaxLength);
    }

    return update(maxLength, newMaxLength);
}

int NonTerminal::getMinLength() const {
    return minLength;
}

int NonTerminal::getMaxLength() const {
    return maxLength;
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

bool NonTerminal::updateMaxLength() {

    int newMaxLength = Grammar::minLength;

    for (const ProductionRule& productionRule : productionRules) {
        newMaxLength = max(productionRule.getMaxLength(), newMaxLength);
    }

    bool changes = update(maxLength, newMaxLength);

    for (ProductionRule& productionRule : productionRules) {
        changes = productionRule.updateMaxLength() || changes;
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

void Grammar::updateMaxLength() {

    bool changes;

    do {

        changes = false;

        for (auto& it : nonTerminals) {
            changes = it.second.updateMaxLength() || changes;
        }
    
    } while (changes);
}

void Grammar::updateLengths() {
    updateMinLength();
    updateMaxLength();
}