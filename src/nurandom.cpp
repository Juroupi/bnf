#include "bnf/grammar.h"

using namespace std;

static auto _s = (srand((unsigned int)chrono::system_clock::now().time_since_epoch().count()), 0);

static float randomFloat(int max) {
    return rand() / (float)RAND_MAX * max;
}

template<class T>
static T& randomElement(vector<T> elements) {
    return elements[rand() % elements.size()];
}

static vector<unsigned int> shuffledIndices(unsigned int n) {

    vector<unsigned int> indices(n);

    for (unsigned int i = 0; i < n; i++) {
        indices[i] = i;
    }

    for (unsigned int i = 0; i < n; i++) {
        std::swap(indices[i], indices[rand() % n]);
    }

    return indices;
}

vector<unsigned int> ProductionRule::getNURandomNonTerminalLengths(unsigned int n) const {

    const unsigned int totaln = n;

    vector<unsigned int> nonTerminalLengths(nonTerminals.size());

    vector<unsigned int> ntmap = shuffledIndices(nonTerminals.size());

    vector<unsigned int> possibleLengths;

    n -= terminalsLength;

    for (size_t ntpos = 0; ntpos < nonTerminals.size(); ntpos++) {

        const NonTerminal& nonTerminal = *nonTerminals[ntmap[ntpos]];

        unsigned int minLength = nonTerminal.getMinLength();
        unsigned int maxLength = getSymbolMaxLength(n, totaln, minLength);

        possibleLengths.clear();

        for (unsigned int i = minLength; i <= maxLength; i++) {

            if (nonTerminal.getExists(i) && getExists(totaln, n - i, ntpos + 1, ntmap)) {
                possibleLengths.push_back(i);
            }
        }

        if (!possibleLengths.empty()) {

            unsigned int length = randomElement(possibleLengths);

            nonTerminalLengths[ntmap[ntpos]] = length;

            n -= length;
        }
    }

    return nonTerminalLengths;
}

void ProductionRule::getNURandomElement(string& element, unsigned int n) const {

    vector<unsigned int> nonTerminalLengths = getNURandomNonTerminalLengths(n);

    unsigned int ntpos = 0;

    for (size_t spos = 0; spos < symbols.size(); spos++) {

        if (ntpos < nonTerminals.size() && symbols[spos] == nonTerminals[ntpos]) {
            symbols[spos]->getNURandomElement(element, nonTerminalLengths[ntpos++]);
        }

        else {
            element += static_cast<const Terminal*>(symbols[spos])->value;
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
    res.reserve(n);
    getNURandomElement(res, n);
    return res;
}