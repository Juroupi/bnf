#include "grammar.h"

#include <iostream>

using namespace std;

void ProductionRule::print(std::ostream& stream) const {

    for (Symbol* const& symbol : symbols) {

        stream << symbol->getValue();

        if (&symbol != &symbols.back()) {
            stream << " ";
        }
    }
}

void NonTerminal::print(std::ostream& stream) const {

    stream << getValue() << " ::= ";

    for (const ProductionRule& productionRule : productionRules) {

        productionRule.print(stream);

        if (&productionRule != &productionRules.back()) {
            stream << " | ";
        }
    }
    
    stream << endl;
}

void Grammar::print(std::ostream& stream) const {

    for (auto& it : nonTerminals) {
        it.second.print(stream);
    }
}