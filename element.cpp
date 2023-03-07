#include "grammar.h"

using namespace std;

void ProductionRule::getElement(string& element, int totaln, int n, big_int& id, int spos, int ntposa) const {

    int ntpos = 0;

    for (Symbol* symbol : symbols) {

        if (ntpos < nonTerminals.size() && symbol == nonTerminals[ntpos]) {

            NonTerminal* symbol = nonTerminals[ntpos];
            
            int minLength = symbol->getMinLength();
            int maxLength = min(n, totaln - (getMinLength() - minLength));

            for (int i = minLength; i <= maxLength; i++) {

                big_int symbolCard;
                symbol->getCardinality(symbolCard, i);

                if (symbolCard > 0) {

                    big_int nextSymbolsCard;
                    getCardinality(nextSymbolsCard, totaln, n - i, ntpos + 1);

                    if (nextSymbolsCard > 0) {

                        big_int totalCard = symbolCard * nextSymbolsCard;

                        if (id < totalCard) {

                            big_int symbolId = id % symbolCard;
                            symbol->getElement(element, i, symbolId);

                            id /= symbolCard;
                            n -= i;
                            ntpos++;

                            break;
                        }

                        id -= totalCard;
                    }
                }
            }
        }

        else {

            big_int nextSymbolsCard;
            getCardinality(nextSymbolsCard, totaln, n, ntpos);

            if (id < nextSymbolsCard) {
                element += static_cast<Terminal*>(symbol)->value;
            }

            else {
                id -= nextSymbolsCard;
            }
        }
    }
}


void ProductionRule::getElement(string& element, int n, big_int& id) const {

    if (n >= getMinLength()) {
        getElement(element, n, n - terminalsLength, id, 0, 0);
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
            return productionRule.getElement(element, n, id);
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