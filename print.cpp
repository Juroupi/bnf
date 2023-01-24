#include "grammar.h"

#include <iostream>

using namespace std;

void ProductionRule::print(bool detailed, std::ostream& stream) const {

    for (Symbol* const& symbol : symbols) {

        stream << symbol->getValue();

        if (&symbol != &symbols.back()) {
            stream << " ";
        }
    }

    if (detailed) {

        stream << "\t; " << "minLength=";

        if (minLength == Grammar::maxMinLength) {
            stream << "inf";
        }

        else {
            stream << minLength;
        }
    }
}

void NonTerminal::print(bool detailed, std::ostream& stream) const {

    stream << getValue() << " ::= ";

    for (const ProductionRule& productionRule : productionRules) {

        productionRule.print(detailed, stream);

        if (&productionRule != &productionRules.back()) {
            
            if (detailed) {
                stream << endl << getValue() << " ::= ";
            }

            else {
                stream << " | ";
            }
        }
    }
    
    stream << endl;
}

void Grammar::print(bool detailed, std::ostream& stream) const {

    for (auto& it : nonTerminals) {
        it.second.print(detailed, stream);
    }
}