#include "grammar.h"

#include <iostream>
#include <fstream>

#include "lexer.h"

using namespace std;

static void syntaxError(const string& message) {
    cerr << "syntax error: " << message << endl;
    exit(1);
}

static Token parseProductionRule(Grammar& grammar, ProductionRule& productionRule, const string& line, int& pos) {

    Token token;
    string value;

    token = readToken(line, pos, value);

    if (token == Token::TERMINAL) {
        productionRule.addSymbol(grammar.addTerminal(value));
    }

    else if (token == Token::NON_TERMINAL) {
        productionRule.addSymbol(grammar.getNonTerminal(value));
    }

    else {
        return token;
    }

    return parseProductionRule(grammar, productionRule, line, pos);
}

static Token parseProductionRules(Grammar& grammar, NonTerminal& nonTerminal, const string& line, int& pos) {

    Token token = parseProductionRule(grammar, nonTerminal.addProductionRule(), line, pos);

    if (token == Token::UNION) {
        return parseProductionRules(grammar, nonTerminal, line, pos);
    }

    return token;
}

void Grammar::parseLine(const string& line, int pos) {

    string nonTerminalName;

    Token token = readToken(line, pos, nonTerminalName);

    if (token == Token::END) {
        return;
    }

    if (token != Token::NON_TERMINAL) {
        syntaxError("non-terminal token expected");
    }

    token = readToken(line, pos);

    if (token != Token::DEFINE) {
        syntaxError("rule definition token expected");
    }

    token = parseProductionRules(*this, getNonTerminal(nonTerminalName), line, pos);

    if (token != Token::END) {
        syntaxError("unexpected token " + tokenName(token));
    }
}

void Grammar::parseFile(const string& name) {

    ifstream file(name);

    if (file) {
        parse(file);
    }

    else {
        cerr << "cannot open the file '" << name << "' in Grammar::parseFile" << endl;
    }
}

void Grammar::parse(istream& stream) {

    string line;

    while (getline(stream, line)) {
        parseLine(line);
    }
}