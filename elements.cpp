#include "grammar.h"

using namespace std;

void ProductionRule::getElements(set<string>& elements, int totaln, int n, int pos, string cur) const {

    if (pos == symbols.size()) {

        if (n == 0) {
            elements.emplace(cur);
        }

        return;
    }

    Symbol* symbol = symbols[pos];

    int minLength = symbol->getMinLength();
    int maxLength = min(n, totaln - (getMinLength() - minLength));

    for (int i = minLength; i <= maxLength; i++) {

        set<string> pieces;

        symbol->getElements(pieces, i);

        for (const string& piece : pieces) {
            getElements(elements, totaln, n - i, pos + 1, cur + piece);
        }
    }
}

void ProductionRule::getElements(set<string>& elements, int n) const {

    if (n >= getMinLength()) {
        getElements(elements, n, n, 0, "");
    }
}

void Terminal::getElements(set<string>& elements, int n) const {

    if (n == value.length()) {
        elements.emplace(value);
    }
}

void NonTerminal::getElements(set<string>& elements, int n) const {

    for (const ProductionRule& productionRule : productionRules) {
        productionRule.getElements(elements, n);
    }
}

void Grammar::getElements(set<string>& elements, const string& nonTerminalName, int n) {
    
    NonTerminal* nonTerminal = getNonTerminal(nonTerminalName, NULL);

    if (nonTerminal != NULL) {
        nonTerminal->getElements(elements, n);
    }
}