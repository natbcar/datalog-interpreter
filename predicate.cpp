#include "predicate.h"

predicate::predicate(string idString, vector<string> paramList)
{
    this->idString = idString;
    this->paramList = paramList;
}
predicate::predicate(string idString, vector<string> paramList, vector<TokenType>& tTypeVector)
{
    this->idString = idString;
    this->paramList = paramList;
    this->tTypeVector = tTypeVector;
}
string predicate::toString()
{
    stringstream ss;
    ss << idString << "(";
    for(unsigned int i = 0; i < paramList.size(); i++){
      if(i == paramList.size() - 1){
        ss << paramList.at(i) << ")";
      }
      else{
        ss << paramList.at(i) << ",";
      }
    }
    return ss.str();
}
vector<string>& predicate::getDomain()
{
    return paramList;
}
string predicate::getID()
{
    return idString;
}
vector<TokenType>& predicate::getType()
{
    return tTypeVector;
}
