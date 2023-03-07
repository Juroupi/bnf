#ifndef _LEXER_H_
#define _LEXER_H_

#include <string>

enum Token {
    INVALID,
    TERMINAL,
    UNFINISHED_TERMINAL,
    NON_TERMINAL,
    UNFINISHED_NON_TERMINAL,
    DEFINE,
    UNION,
    END
};

Token readToken(const std::string& line, int& pos, std::string& value);

Token readToken(const std::string& line, int& pos);

std::string tokenName(Token token);

#endif