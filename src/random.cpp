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