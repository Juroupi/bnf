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

void ProductionRule::getNURandomElement(string& element, unsigned int n) const {

    const unsigned int totaln = n;

    unsigned int ntpos = 0;

    vector<unsigned int> possibleLengths;

    n -= terminalsLength;

    for (const Symbol* symbol : symbols) {

        if (ntpos < nonTerminals.size() && symbol == nonTerminals[ntpos]) {

            const NonTerminal& nonTerminal = *nonTerminals[ntpos];

            unsigned int minLength = nonTerminal.getMinLength();
            unsigned int maxLength = getSymbolMaxLength(n, totaln, minLength);

            possibleLengths.clear();

            for (unsigned int i = minLength; i <= maxLength; i++) {

                if (nonTerminal.getExists(i) && getExists(totaln, n - i, ntpos + 1)) {
                    possibleLengths.push_back(i);
                }
            }

            if (!possibleLengths.empty()) {

                unsigned int length = randomElement(possibleLengths);

                nonTerminal.getNURandomElement(element, length);

                n -= length;
                ntpos++;
            }
        }

        else {
            element += static_cast<const Terminal*>(symbol)->value;
        }
    }
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