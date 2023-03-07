#include "grammar.h"

#include <ctime>

using namespace std;

static rand_state randState;

void Grammar::getRandomElement(string& element, const string& nonTerminalName, int n) const {
    big_int card, id;
    getCardinality(card, nonTerminalName, n);
    id = randState.get(card);
    getElement(element, nonTerminalName, n, id);
}