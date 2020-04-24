#pragma once

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//enum that specifies the different types of tokens
enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, END};

class token {
    private:
    string tokenStr;
    int lineNum;
    TokenType tType;

    public:
    token(string tokenStr, int lineNum, TokenType tType);
    string toString();
    string tokenToString(TokenType tType);
    TokenType getType();
    string getTokenStr();
};
