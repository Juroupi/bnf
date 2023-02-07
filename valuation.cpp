#include "grammar.h"

#include <climits>

using namespace std;

static int addLengths(int v1, int v2) {
    return min(Grammar::maxLength, v1 + v2);
}

int ProductionRule::getMinLength() const {
    return minLength;
}

void ProductionRule::computeMinLength(set<void*>& visited) {

    if (minLength == Grammar::maxLength && visited.find(this) == visited.end()) {

        if (symbols.size() == 2) cout << "skjgjg" << endl;

        int newMinLength = terminalsLength;

        visited.emplace(this);

        for (NonTerminal* nonTerminal : nonTerminals) {
            nonTerminal->computeMinLength(visited);
            newMinLength = addLengths(nonTerminal->getMinLength(), newMinLength);
        }

        visited.erase(this);

        minLength = newMinLength;
    }
}

int NonTerminal::getMinLength() const {
    return minLength;
}

void NonTerminal::computeMinLength(set<void*>& visited) {

    if (minLength == Grammar::maxLength && visited.find(this) == visited.end()) {

        // int newMinLength = Grammar::maxLength;
        
        visited.emplace(this);

        for (ProductionRule& productionRule : productionRules) {
            productionRule.computeMinLength(visited);
            // newMinLength = min(productionRule.getMinLength(), newMinLength);
            minLength = min(productionRule.getMinLength(), minLength);
        }

        visited.erase(this);

        // minLength = newMinLength;
    }
}

void Grammar::computeMinLength() {

    set<void*> visited;

    for (auto& it : nonTerminals) {
        it.second.computeMinLength(visited);
    }
}