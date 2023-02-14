#include "grammar.h"

#include <climits>

using namespace std;

ProductionRule::ProductionRule() :
    terminalsLength(0), minLength(Grammar::maxLength), nonTerminals(), symbols() {}

void ProductionRule::addSymbol(Terminal& terminal) {
    terminalsLength += terminal.value.length();
    symbols.push_back(&terminal);
}

void ProductionRule::addSymbol(NonTerminal& nonTerminal) {
    nonTerminals.push_back(&nonTerminal);
    symbols.push_back(&nonTerminal);
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
    name(name), minLength(Grammar::maxLength), productionRules(), cardinalities() {}

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

void NonTerminal::reserveMemory(int n) {
    cardinalities.reserve(n);
}

void NonTerminal::clearMemory() {
    cardinalities.clear();
}

const int Grammar::maxLength = INT_MAX / 2;

Grammar::Grammar() :
    terminals(), nonTerminals() {}

Grammar::Grammar(const string& fileName) : Grammar() {
    parseFile(fileName);
    updateMinLength();
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

NonTerminal* Grammar::getNonTerminal(const std::string& name, NonTerminal* def) {

    auto it = nonTerminals.find(name);

    if (it == nonTerminals.end()) {
        return def;
    }

    return &it->second;
}

void Grammar::reserveMemory(int n) {
    for (auto& it : nonTerminals) {
        it.second.reserveMemory(n);
    }
}

void Grammar::clearMemory() {
    for (auto& it : nonTerminals) {
        it.second.clearMemory();
    }
}