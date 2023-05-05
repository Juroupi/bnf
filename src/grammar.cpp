#include "bnf/grammar.h"

#include <climits>

using namespace std;

ProductionRule::ProductionRule() :
    terminalsLength(0), minLength(Grammar::maxLength), nonTerminals(), symbols(),
    startProbability(1), endProbability(1) {}

void ProductionRule::addSymbol(Terminal& terminal) {
    terminalsLength += terminal.value.length();
    symbols.push_back(&terminal);
}

void ProductionRule::addSymbol(NonTerminal& nonTerminal) {
    nonTerminals.push_back(&nonTerminal);
    symbols.push_back(&nonTerminal);
}

unsigned int ProductionRule::getSymbolMaxLength(unsigned int n, unsigned int totaln, unsigned int minLength) const {
    
    // la longueur de ce symbole ne peut pas être plus grande
    // que la longueur totale de la règle moins la somme de la longueur
    // minimale des autres symboles

    unsigned int othersMinLength = getMinLength() - minLength;

    if (totaln <= othersMinLength) {
        return 0;
    }

    return min(n, totaln - othersMinLength);
}

float ProductionRule::getProbability(float x) const {
    return x * (endProbability - startProbability) + startProbability;
}

Terminal::Terminal(const std::string& value) :
    value(value) {}

string Terminal::getValue(bool raw) const {

    if (raw) {
        return value;
    }

    return "\"" + value + "\"";
}

NonTerminal::NonTerminal(const string& name) :
    minLength(Grammar::maxLength), name(name) {}

ProductionRule& NonTerminal::addProductionRule() {
    productionRules.emplace_back();
    return productionRules.back();
}

string NonTerminal::getValue(bool raw) const {

    if (raw) {
        return name;
    }

    return "<" + name + ">";
}

void NonTerminal::reserveMemory(unsigned int n) const {
    cardinalities.reserve(n);
    existences.reserve(n);
}

void NonTerminal::clearMemory() const {
    cardinalities.clear();
    existences.clear();
}

float NonTerminal::getProbabilitySum(unsigned int n) const {

    float sum = 0;

    for (auto& productionRule : productionRules) {
        
        if (productionRule.getExists(n)) {
            sum += productionRule.getProbability();
        }
    }

    return sum;
}

float NonTerminal::getProbabilitySum(float x) const {

    float sum = 0;

    for (auto& productionRule : productionRules) {
        sum += productionRule.getProbability(x);
    }
    
    return sum;
}

const unsigned int Grammar::maxLength = UINT_MAX / 2;

Grammar::Grammar() {}

Grammar::Grammar(const string& fileName) {
    parseFile(fileName);
    updateMinLengths();
}

Terminal& Grammar::addTerminal(const std::string& value) {
    terminals.emplace_back(value);
    return terminals.back();
}

NonTerminal& Grammar::getNonTerminal(const string& name) {
    return nonTerminals.emplace(name, name).first->second;
}

NonTerminal& Grammar::operator[](const string& name) {
    return getNonTerminal(name);
}

void Grammar::reserveMemory(unsigned int n) const {
    for (const auto& it : nonTerminals) {
        it.second.reserveMemory(n);
    }
}

void Grammar::clearMemory() const {
    for (const auto& it : nonTerminals) {
        it.second.clearMemory();
    }
}