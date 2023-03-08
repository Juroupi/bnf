#include "bnf/grammar.h"

using namespace std;

void ProductionRule::getElement(string& element, unsigned int n, big_int& id) const {

    if (n < getMinLength()) {
        return;
    }

    const unsigned int totaln = n;

    unsigned int ntpos = 0;

    n -= terminalsLength;

    for (const Symbol* symbol : symbols) {

        if (ntpos < nonTerminals.size() && symbol == nonTerminals[ntpos]) {

            const NonTerminal* symbol = nonTerminals[ntpos];
            
            unsigned int minLength = symbol->getMinLength();
            unsigned int maxLength = getSymbolMaxLength(n, totaln, minLength);

            for (unsigned int i = minLength; i <= maxLength; i++) {

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
                element += static_cast<const Terminal*>(symbol)->value;
            }

            else {
                id -= nextSymbolsCard;
            }
        }
    }
}

void Terminal::getElement(string& elements, unsigned int n, big_int& id) const {

    if (id == 0 && n == value.length()) {
        elements += value;
    }
}

void NonTerminal::getElement(string& element, unsigned int n, big_int& id) const {

    big_int card;

    for (const ProductionRule& productionRule : productionRules) {

        productionRule.getCardinality(card, n);

        if (id < card) {
            return productionRule.getElement(element, n, id);
        }

        id -= card;
    }
}

string NonTerminal::getElement(unsigned int n, const big_int& id) const {
    string res;
    big_int tmp = id;
    getElement(res, n, tmp);
    return res;
}