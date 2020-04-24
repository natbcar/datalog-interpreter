#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include "parameter.h"
#include "token.h"

using namespace std;

class predicate{
    private:
      string idString;
      vector<string> paramList;
      vector<TokenType> tTypeVector;
    public:
      predicate(string idString, vector<string> paramList);
      predicate(string idString, vector<string> paramList, vector<TokenType>& tTypeVector);
      string toString(); //converts predicate object into string
      vector<string>& getDomain();
      string getID(); //returns ID string
      vector<TokenType>& getType();
};
