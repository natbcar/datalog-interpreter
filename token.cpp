#include "token.h"

token::token(string tokenStr, int lineNum, TokenType tType)
{
    //creates token and assigns parameters to private class variables
    this->tokenStr = tokenStr;
    this->lineNum = lineNum;
    this->tType = tType;
}
string token::toString()
{
    string tokenString;

    //converts line num to string
    stringstream ss;
    ss << lineNum;
    string lineStr = ss.str();

    //converts tokens to correct out put format
    tokenString.append("(");
    tokenString.append(tokenToString(tType));
    tokenString.append(",");
    tokenString.append("\"");
    tokenString.append(tokenStr);
    tokenString.append("\"");
    tokenString.append(",");
    tokenString.append(lineStr);
    tokenString.append(")");

    //returns token with type and line # in a string
    return tokenString;
}
string token::tokenToString(TokenType tType)
{
    //switch statement that converts token type to string
    switch(tType){
        case COMMA: return "COMMA"; break;
        case PERIOD: return "PERIOD"; break;
        case Q_MARK: return "Q_MARK"; break;
        case LEFT_PAREN: return "LEFT_PAREN"; break;
        case RIGHT_PAREN: return "RIGHT_PAREN"; break;
        case COLON: return "COLON"; break;
        case COLON_DASH: return "COLON_DASH"; break;
        case MULTIPLY: return "MULTIPLY"; break;
        case ADD: return "ADD"; break;
        case SCHEMES: return "SCHEMES"; break;
        case FACTS: return "FACTS"; break;
        case RULES: return "RULES"; break;
        case QUERIES: return "QUERIES"; break;
        case ID: return "ID"; break;
        case STRING: return "STRING"; break;
        case COMMENT: return "COMMENT"; break;
        case UNDEFINED: return "UNDEFINED"; break;
        case END: return "EOF"; break;
    }
    return "ERROR";
}
TokenType token::getType()
{
    return tType;
}
string token::getTokenStr()
{
    return tokenStr;
}
