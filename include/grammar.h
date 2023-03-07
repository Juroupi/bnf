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


struct Symbol {
    virtual std::string getValue(bool raw = false) const = 0;
    virtual void getCardinality(big_int& res, int n) const = 0;
    virtual void getElements(std::set<std::string>& elements, int n) const = 0;
    virtual void getElement(std::string& element, int n, big_int& id) const = 0;
    virtual int getMinLength() const = 0;
};


class Terminal;
class NonTerminal;

class ProductionRule {

    int terminalsLength, minLength;
    std::vector<NonTerminal*> nonTerminals;
    std::vector<Symbol*> symbols;

    void getCardinality(big_int& res, int totaln, int n, int ntpos) const;
    
    void getElements(std::set<std::string>& elements, int totaln, int n, int spos, std::string cur) const;
    
public:

    ProductionRule();

    void addSymbol(Terminal& terminal);
    void addSymbol(NonTerminal& nonTerminal);

    void getCardinality(big_int& res, int n) const;

    void getElements(std::set<std::string>& elements, int n) const;

    void getElement(std::string& element, int n, big_int& id) const;

    int getMinLength() const;
    bool updateMinLength();

    void print(bool detailed = false, std::ostream& stream = std::cout) const;
};


struct Terminal : public Symbol {

    const std::string value;

    Terminal(const std::string& value);

    std::string getValue(bool raw = false) const override;

    void getCardinality(big_int& res, int n) const override;

    void getElements(std::set<std::string>& elements, int n) const override;

    void getElement(std::string& element, int n, big_int& id) const override;

    int getMinLength() const override;
};


class NonTerminal : public Symbol {

    int minLength;
    std::vector<ProductionRule> productionRules;
    mutable std::vector<std::unique_ptr<big_int>> cardinalities;

public:

    const std::string name;

    NonTerminal(const std::string& name);

    ProductionRule& addProductionRule();

    std::string getValue(bool raw = false) const override;

    void getCardinality(big_int& res, int n) const override;
    big_int getCardinality(int n) const;
    void reserveMemory(int n) const;
    void clearMemory() const;

    void getElements(std::set<std::string>& elements, int n) const override;
    std::set<std::string> getElements(int n) const;

    void getElement(std::string& element, int n, big_int& id) const override;
    std::string getElement(int n, big_int& id) const;

    int getMinLength() const override;
    bool updateMinLength();

    void getRandomElement(std::string& element, int n) const;
    std::string getRandomElement(int n) const;

    void print(bool detailed = false, std::ostream& stream = std::cout) const;
};


class Grammar {

    std::list<Terminal> terminals;
    std::map<std::string, NonTerminal> nonTerminals;

public:

    static const int maxLength;

    Grammar(const std::string& fileName);

    Terminal& addTerminal(const std::string& value);

    NonTerminal& getNonTerminal(const std::string& name);
    NonTerminal& operator[](const std::string& name);

    void getCardinality(big_int& cardinality, const std::string& nonTerminalName, int n) const;
    big_int getCardinality(const std::string& nonTerminalName, int n) const;
    void reserveMemory(int n) const;
    void clearMemory() const;

    void updateMinLengths();

    void parse(std::istream& stream);
    void parseFile(const std::string& name);
    void parseLine(const std::string& line, int pos = 0);

    void print(bool detailed = false, std::ostream& stream = std::cout) const;
};

#endif