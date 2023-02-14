#include "grammar.h"

#include <ctime>

using namespace std;

static rand_state randState;

void ProductionRule::getElement(string& element, int totaln, int n, big_int& id, int spos, int ntpos) const {

    if (spos == symbols.size()) {
        return;
    }

    if (ntpos == nonTerminals.size()) {
        
        for (int i = spos; i < symbols.size(); i++) {
            element += symbols[i]->getValue(true);
        }

        return;
    }

    Symbol* symbol = symbols[spos];

    int minLength = symbol->getMinLength();
    int maxLength = min(n, totaln - (getMinLength() - minLength));

    for (int i = minLength; i <= maxLength; i++) {

        big_int symbolCard;
        symbol->getCardinality(symbolCard, i);
        
        if (symbolCard != 0) {

            big_int nextSymbolCard;
            getCardinality(nextSymbolCard, totaln, n - i, ntpos + 1);

            big_int card = symbolCard * nextSymbolCard;

            if (id < card) {
            
                string piece;

                big_int symbolId = id / nextSymbolCard;
                big_int nextSymbolId = id % nextSymbolCard;

                symbol->getElement(piece, i, symbolId);

                element += piece;

                if (symbols[spos] == nonTerminals[ntpos]) {
                    ntpos++;
                }

                getElement(element, totaln, n - i, nextSymbolId, spos + 1, ntpos);

                return;
            }

            id -= card;
        }
    }
}

void ProductionRule::getElement(string& element, int n, big_int& id) const {

    if (n >= getMinLength()) {
        getElement(element, n, n, id, 0, 0);
    }
}

void Terminal::getElement(string& elements, int n, big_int& id) const {

    if (id == 0 && n == value.length()) {
        elements += value;
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