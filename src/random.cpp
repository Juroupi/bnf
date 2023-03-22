#include "bnf/grammar.h"

#include <cstdlib>
#include <ctime>

using namespace std;

static rand_state randState;

static float randomFloat(int max) {
    static auto _s = (srand((unsigned int)std::chrono::system_clock::now().time_since_epoch().count()), 0);
    return rand() / (float)RAND_MAX * max;
}

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

        float limit = randomFloat(probabilitySum), sum = 0;

        for (const auto& productionRule : productionRules) {

            sum += productionRule.probability;

            if (sum >= limit) {
                return productionRule.getRandomElementOfHeight(element, n);
            }
        }
    }
}

void ProductionRule::getRandomElementOfHeight(string& element, unsigned int n) const {
    
    for (const Symbol* symbol : symbols) {
        symbol->getRandomElementOfHeight(element, n - 1);
    }
}