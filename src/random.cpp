#include "bnf/grammar.h"

#include <ctime>

using namespace std;

static rand_state randState;

void NonTerminal::getRandomElement(string& element, unsigned int n) const {
    big_int card, id;
    getCardinality(card, n);
    id = randState.get(card);
    getElement(element, n, id);
}

string NonTerminal::getRandomElement(unsigned int n) const {
    string res;
    getRandomElement(res, n);
    return res;
}

string NonTerminal::getRandomElementOfHeight(unsigned int n) const {
    string res;
    getRandomElementOfHeight(res, n);
    return res;
}

void Terminal::getRandomElementOfHeight(string& element, unsigned int n) const {
    
    if (n > 0) {
        element += value;
    }
}

void NonTerminal::getRandomElementOfHeight(string& element, unsigned int n) const {
    
    if (n > 0) {
        auto i = randState.get(productionRules.size()).get_ui();
        productionRules[i].getRandomElementOfHeight(element, n);
    }
}

void ProductionRule::getRandomElementOfHeight(string& element, unsigned int n) const {
    
    for (const Symbol* symbol : symbols) {
        symbol->getRandomElementOfHeight(element, n - 1);
    }
}