#ifndef _GRAMMAR_H_
#define _GRAMMAR_H_

#include <iostream>
#include <istream>
#include <ostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <utility>

#include "big_int.h"


class Symbol {
public:
    virtual std::string getValue() const = 0;
};

class Terminal;
class NonTerminal;


class ProductionRule {

    int terminalsLength;
    std::vector<NonTerminal*> nonTerminals;
    std::vector<Symbol*> symbols;

public:

    ProductionRule();

    void addSymbol(Terminal& terminal);
    void addSymbol(NonTerminal& nonTerminal);

    void print(std::ostream& stream = std::cout) const;

    big_int getCardinality(int n, int pos = 0) const;
};


class Terminal : public Symbol {

public:

    const std::string value;

    Terminal(const std::string& value);

    std::string getValue() const override;
};


class NonTerminal : public Symbol {

    std::vector<ProductionRule> productionRules;
    std::vector<std::pair<bool, big_int>> cardinalities;

public:

    const std::string name;

    NonTerminal(const std::string& name);

    ProductionRule& addProductionRule();

    std::string getValue() const override;

    void print(std::ostream& stream) const;

    big_int getCardinality(int n);
};


class Grammar {

    std::list<Terminal> terminals;
    std::map<std::string, NonTerminal> nonTerminals;

public:

    Grammar();
    Grammar(const std::string& fileName);

    Terminal& addTerminal(const std::string& value);
    NonTerminal& getNonTerminal(const std::string& name);
    NonTerminal& operator[](const std::string& name);
    NonTerminal* getNonTerminal(const std::string& name, NonTerminal* def);

    void parse(std::istream& stream);
    void parseFile(const std::string& name);
    void parseLine(const std::string& line, int pos = 0);

    void print(std::ostream& stream = std::cout) const;

    big_int getCardinality(const std::string& nonTerminalName, int n);
};

#endif