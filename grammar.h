#ifndef _GRAMMAR_H_
#define _GRAMMAR_H_

#include <iostream>
#include <istream>
#include <ostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <memory>

#include "big_int.h"


class Symbol {
public:
    virtual std::string getValue() const = 0;
    virtual void getElements(std::set<std::string>& elements, int n) const = 0;
};

class Terminal;
class NonTerminal;


class ProductionRule {

    int terminalsLength;
    std::vector<NonTerminal*> nonTerminals;
    std::vector<Symbol*> symbols;

    void getElements(std::set<std::string>& elements, int n, int pos, std::string cur) const;

public:

    ProductionRule();

    void addSymbol(Terminal& terminal);
    void addSymbol(NonTerminal& nonTerminal);

    void print(std::ostream& stream = std::cout) const;

    void getCardinality(big_int& res, int n, int pos = 0) const;

    void getElements(std::set<std::string>& elements, int n) const;
};


class Terminal : public Symbol {

public:

    const std::string value;

    Terminal(const std::string& value);

    std::string getValue() const override;

    void getElements(std::set<std::string>& elements, int n) const override;
};


class NonTerminal : public Symbol {

    std::vector<ProductionRule> productionRules;
    std::vector<std::unique_ptr<big_int>> cardinalities;

public:

    const std::string name;

    NonTerminal(const std::string& name);

    ProductionRule& addProductionRule();

    std::string getValue() const override;

    void print(std::ostream& stream) const;

    void getCardinality(big_int& res, int n);
    big_int getCardinality(int n);

    void getElements(std::set<std::string>& elements, int n) const override;
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

    void getCardinality(big_int& cardinality, const std::string& nonTerminalName, int n);
    big_int getCardinality(const std::string& nonTerminalName, int n);

    void getElements(std::set<std::string>& elements, const std::string& nonTerminalName, int n);
};

#endif