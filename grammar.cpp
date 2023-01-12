#include "grammar.h"

using namespace std;

ProductionRule::ProductionRule() :
    terminalsLength(0), nonTerminals(), symbols() {}

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

string Terminal::getValue() const {
    return "\"" + value + "\"";
}

NonTerminal::NonTerminal(const string& name) :
    name(name), productionRules() {}

ProductionRule& NonTerminal::addProductionRule() {
    productionRules.emplace_back();
    return productionRules.back();
}

string NonTerminal::getValue() const {
    return "<" + name + ">";
}

Grammar::Grammar() :
    terminals(), nonTerminals() {}

Grammar::Grammar(const string& fileName) : Grammar() {
    parseFile(fileName);
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

const NonTerminal* Grammar::getNonTerminal(const std::string& name) const {

    auto it = nonTerminals.find(name);

    if (it == nonTerminals.end()) {
        return NULL;
    }

    return &it->second;
}