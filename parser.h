#pragma once

#include "token.h"
#include "DatalogProgram.h"
#include "scanner.h"
#include "rule.h"
#include "predicate.h"
#include "parameter.h"
#include "Interpreter.h"
#include <vector>

using namespace std;

class parser {
    private:
      int n; //used to iterate through the token vector
      vector<token> tokens; //stores tokens to be parsed through
      vector<predicate> schemes;
      vector<predicate> facts;
      vector<predicate> queries;
      vector<rule> rules;
    public:
      parser(vector<token>& tokenVector);
      bool match(token next, TokenType correct);
      void parse();
      DatalogProgram parseDLP();
      void parseScheme(vector<predicate>& schemeVector);
      void parseSchemeList(vector<predicate>& schemeVector);
      void parseFactList(vector<predicate>& factVector);
      void parseFact(vector<predicate>& factVector);
      void parseRuleList(vector<rule>& ruleVector);
      void parseRule(vector<rule>& ruleVector);
      void parseQuery(vector<predicate>& queryVector);
      void parseQueryList(vector<predicate>& queryVector);
      predicate parseHeadPredicate();
      void parsePredicate(vector<predicate>& predicateVector);
      void parsePredicateList(vector<predicate>& predicateVector);
      void parseParameterList(vector<string>& paramVector,vector<TokenType>& tTypeVector);
      void parseParameter(vector<string>& paramVector, vector<TokenType>& tTypeVector);
      void parseStringList(vector<string>& stringList);
      void parseIDList(vector<string>& idList);
      string parseExpression();
      void parseOperator(string& expression);
};
