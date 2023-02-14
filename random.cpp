#include "grammar.h"

#include <ctime>

using namespace std;

static rand_state randState;

void ProductionRule::getElement(string& element, int totaln, int n, big_int& id, int pos, string cur) const {

    if (pos == symbols.size()) {

        if (n == 0) {
            element = cur;
        }

        return;
    }

    Symbol* symbol = symbols[pos];

    int minLength = symbol->getMinLength();
    int maxLength = min(n, totaln - (getMinLength() - minLength));

    for (int i = minLength; i <= maxLength; i++) {

        big_int card;

        symbol->getCardinality(card, i);

        if (id < card) {

            string piece;

            symbol->getElement(piece, i, id);

            getElement(element, totaln, n - i, id, pos + 1, cur + piece);

            return;
        }

        id -= card;
    }
}

void ProductionRule::getElement(string& element, int n, big_int& id) const {

    if (n >= getMinLength()) {
        getElement(element, n, n, id, 0, "");
    }
}

void Terminal::getElement(string& elements, int n, big_int& id) const {

    if (id == 0 && n == value.length()) {
        elements = value;
    }
}

void NonTerminal::getElement(string& element, int n, big_int& id) const {

    big_int card;

    for (const ProductionRule& productionRule : productionRules) {

        productionRule.getCardinality(card, n);

        if (id < card) {
            productionRule.getElement(element, n, id);
            return;
        }

        id -= card;
    }
}

void Grammar::getElement(string& element, const string& nonTerminalName, int n, big_int& id) {
    
    NonTerminal* nonTerminal = getNonTerminal(nonTerminalName, NULL);

    if (nonTerminal != NULL) {
        nonTerminal->getElement(element, n, id);
    }
}

void Grammar::getRandomElement(string& element, const string& nonTerminalName, int n) {
    big_int card, id;
    getCardinality(card, nonTerminalName, n);
    id = randState.get(card);
    getElement(element, nonTerminalName, n, id);
}