#include "grammar.h"

using namespace std;

void ProductionRule::getElements(set<string>& elements, unsigned int totaln, unsigned int n, unsigned int spos, string cur) const {
    
    if (spos == symbols.size()) {

        if (n == 0) {
            elements.emplace(cur);
        }

        return;
    }

    const Symbol* symbol = symbols[spos];

    unsigned int minLength = symbol->getMinLength();
    unsigned int maxLength = getSymbolMaxLength(n, totaln, minLength);

    for (unsigned int i = minLength; i <= maxLength; i++) {

        set<string> pieces;

        symbol->getElements(pieces, i);

        for (const string& piece : pieces) {
            getElements(elements, totaln, n - i, spos + 1, cur + piece);
        }
    }
}

void ProductionRule::getElements(set<string>& elements, unsigned int n) const {

    if (n >= getMinLength()) {
        getElements(elements, n, n, 0, "");
    }
}

void Terminal::getElements(set<string>& elements, unsigned int n) const {

    if (n == value.length()) {
        elements.emplace(value);
    }
}

void NonTerminal::getElements(set<string>& elements, unsigned int n) const {

    for (const ProductionRule& productionRule : productionRules) {
        productionRule.getElements(elements, n);
    }
}

set<string> NonTerminal::getElements(unsigned int n) const {
    set<string> res;
    getElements(res, n);
    return res;
}