#include "bnf/grammar.h"

using namespace std;

static big_int id;

static float randomFloat(int max) {
    static auto _s = (srand((unsigned int)chrono::system_clock::now().time_since_epoch().count()), 0);
    return rand() / (float)RAND_MAX * max;
}

template<class T>
static T& randomElement(vector<T> elements) {
    return elements[rand() % elements.size()];
}

void ProductionRule::getNURandomElement(string& element, unsigned int totaln, unsigned int n, unsigned int spos, unsigned int ntpos) const {
    
    if (spos >= symbols.size()) {
        return;
    }

    if (ntpos < nonTerminals.size() && symbols[spos] == nonTerminals[ntpos]) {

        const NonTerminal& nonTerminal = *nonTerminals[ntpos];

        unsigned int minLength = nonTerminal.getMinLength();
        unsigned int maxLength = getSymbolMaxLength(n, totaln, minLength);

        vector<unsigned int> possibleLengths;

        for (unsigned int i = minLength; i <= maxLength; i++) {

            if (nonTerminal.getExists(i) && getExists(totaln, n - i, ntpos + 1)) {
                possibleLengths.push_back(i);
            }
        }

        if (!possibleLengths.empty()) {

            unsigned int length = randomElement(possibleLengths);

            nonTerminal.getNURandomElement(element, length);

            getNURandomElement(element, totaln, n - length, spos + 1, ntpos + 1);
        }
    }

    else {

        const Terminal& terminal = *static_cast<const Terminal*>(symbols[spos]);

        element += terminal.value;

        getNURandomElement(element, totaln, n, spos + 1, ntpos);
    }
}

void ProductionRule::getNURandomElement(string& element, unsigned int n) const {

    getNURandomElement(element, n, n - terminalsLength, 0, 0);
}

void Terminal::getNURandomElement(string& elements, unsigned int n) const {

    if (n == value.length()) {
        elements += value;
    }
}

void NonTerminal::getNURandomElement(string& element, unsigned int n) const {

    float limit = randomFloat(getProbabilitySum(n)), sum = 0;

    for (const auto& productionRule : productionRules) {

        if (productionRule.getExists(n)) {

            sum += productionRule.getProbability();

            if (sum > limit) {
                return productionRule.getNURandomElement(element, n);
            }
        }
    }
}

string NonTerminal::getNURandomElement(unsigned int n) const {
    string res;
    getNURandomElement(res, n);
    return res;
}