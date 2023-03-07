#include "lexer.h"

#include <iostream>
#include <cctype>

using namespace std;

static const string tokenNames[] = {
    "INVALID",
    "TERMINAL",
    "UNFINISHED_TERMINAL",
    "NON_TERMINAL",
    "UNFINISHED_NON_TERMINAL",
    "DEFINE",
    "UNION",
    "END"
};

static bool readNext(const string& line, int& pos, const string& next) {

    for (char c : next) {

        if (c != line[pos]) {
            return false;
        }

        pos++;
    }

    return true;
}

static bool readValue(const string& line, int& pos, string& value, char delimiter) {

    while (line[pos] != delimiter) {

        if (line[pos] == '\0') {
            return false;
        }

        value += line[pos++];
    }

    return true;
}

Token _readToken(const string& line, int& pos, string& value) {

    value.clear();
    
    if (line[pos] == '<') {
        return readValue(line, ++pos, value, '>')
            ? Token::NON_TERMINAL
            : Token::UNFINISHED_NON_TERMINAL;
    }

    else if (line[pos] == '"') {
        return readValue(line, ++pos, value, '"')
            ? Token::TERMINAL
            : Token::UNFINISHED_TERMINAL;
    }

    else if (line[pos] == '\'') {
        return readValue(line, ++pos, value, '\'')
            ? Token::TERMINAL
            : Token::UNFINISHED_TERMINAL;
    }

    else if (line[pos] == ':') {
        return readNext(line, ++pos, ":=")
            ? Token::DEFINE
            : Token::INVALID;
    }

    else if (line[pos] == '|') {
        return Token::UNION;
    }

    else if (line[pos] == '\0' || line[pos] == ';') {
        return Token::END;
    }

    else if (isspace(line[pos])) {
        return _readToken(line, ++pos, value);
    }

    value += line[pos];

    return Token::INVALID;
}

Token readToken(const string& line, int& pos, string& value) {
    Token token = _readToken(line, pos, value);
    pos++;
    return token;
}

Token readToken(const std::string& line, int& pos) {
    string value;
    return readToken(line, pos, value);
}

string tokenName(Token token) {
    return tokenNames[token];
}