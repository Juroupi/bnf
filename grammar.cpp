#include "grammar.h"

using namespace std;

DerivationTree::DerivationTree(const Symbol* root) :
    root(root) {}

DerivationTree::Derivation::Derivation(const Symbol* symbol) :
    symbol(symbol) {}

DerivationTree::Derivation& DerivationTree::Derivation::addDerivation(const Symbol* symbol) {
    derivations.emplace_back(symbol);
    return derivations.back();
}

const vector<DerivationTree::Derivation>& DerivationTree::Derivation::getDerivations() const {
    return derivations;
}

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

string Terminal::getValue(bool raw) const {

    if (raw) {
        return value;
    }

    return "\"" + value + "\"";
}

NonTerminal::NonTerminal(const string& name) :
    name(name), productionRules(), cardinalities() {}

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

NonTerminal* Grammar::getNonTerminal(const std::string& name, NonTerminal* def) {

    auto it = nonTerminals.find(name);

    if (it == nonTerminals.end()) {
        return def;
    }

    return &it->second;
}