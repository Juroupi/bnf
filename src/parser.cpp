#include "bnf/grammar.h"

#include <iostream>
#include <fstream>

#include "bnf/lexer.h"

using namespace std;

static void syntaxError(const string& message) {
    cerr << "syntax error: " << message << endl;
    exit(1);
}

static void parseProbability(Grammar& grammar, ProductionRule& productionRule, const string& value) {

    unsigned int dashPos = value.find('-');

    if (dashPos == string::npos) {
        productionRule.startProbability = std::stof(value);
        productionRule.endProbability = productionRule.startProbability;
    }

    else {
        productionRule.startProbability = std::stof(value.substr(0, dashPos));
        productionRule.endProbability = std::stof(value.substr(dashPos + 1));
    }
}

static Token parseProductionRule(Grammar& grammar, ProductionRule& productionRule, const string& line, unsigned int& pos) {

    Token token;
    string value;

    token = readToken(line, pos, value);

    if (token == Token::TERMINAL) {
        productionRule.addSymbol(grammar.addTerminal(value));
    }

    else if (token == Token::NON_TERMINAL) {
        productionRule.addSymbol(grammar.getNonTerminal(value));
    }

    else if (token == Token::PROBABILITY) {
        parseProbability(grammar, productionRule, value);
    }

    else {
        return token;
    }

    return parseProductionRule(grammar, productionRule, line, pos);
}

static Token parseProductionRules(Grammar& grammar, NonTerminal& nonTerminal, const string& line, unsigned int& pos) {

    Token token = parseProductionRule(grammar, nonTerminal.addProductionRule(), line, pos);

    if (token == Token::UNION) {
        return parseProductionRules(grammar, nonTerminal, line, pos);
    }

    return token;
}

void Grammar::parseLine(const string& line, unsigned int pos) {

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

    auto& nonTerminal = getNonTerminal(nonTerminalName);

    token = parseProductionRules(*this, nonTerminal, line, pos);

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