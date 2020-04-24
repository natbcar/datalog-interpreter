#include "parser.h"

parser::parser(vector<token>& tokenVector)
{
    tokens = tokenVector;
}
bool parser::match(token next, TokenType correct)
{
    if(next.getType() == correct){
      return true;
    }
    else{
      return false;
    }
}
void parser::parse()
{
    DatalogProgram dlp = DatalogProgram();
    n = 0; //initializing starting point to beginning of the vector
    //bool exception_caught = false;  //marked true if exception is caught
    try{                            //if not prints "Success!" statement
      dlp = parseDLP(); //begining recursive descent parsing
    }catch (token error){
      //exception_caught = true;
      cout << "Failure!" << endl;
      cout << "  " << error.toString() << endl;
    }
    //if(!exception_caught){
      //cout << "Success!" << endl;
      //cout << dlp.toString();
    //}
    Interpreter newInterpreter = Interpreter(dlp);
    newInterpreter.processInput();
}
DatalogProgram parser::parseDLP()
{
    if(match(tokens.at(n),SCHEMES)){
      n++;
    }
    else{
      throw tokens.at(n);
    }
    if(match(tokens.at(n),COLON)){
      n++;
    }
    else{
      throw tokens.at(n);
    }
    parseScheme(schemes);
    parseSchemeList(schemes);
    if(match(tokens.at(n),FACTS)){
      n++;
    }
    else{
      throw tokens.at(n);
    }
    if(match(tokens.at(n),COLON)){
      n++;
    }
    else{
      throw tokens.at(n);
    }
    parseFactList(facts);
    if(match(tokens.at(n),RULES)){
      n++;
    }
    else{
      throw tokens.at(n);
    }
    if(match(tokens.at(n),COLON)){
      n++;
    }
    else{
      throw tokens.at(n);
    }
    parseRuleList(rules);
    if(match(tokens.at(n),QUERIES)){
      n++;
    }
    else{
      throw tokens.at(n);
    }
    if(match(tokens.at(n),COLON)){
      n++;
    }
    else{
      throw tokens.at(n);
    }
    parseQuery(queries);
    parseQueryList(queries);
    return DatalogProgram(rules, schemes, facts, queries);
}
void parser::parseScheme(vector<predicate>& schemeVector)
{
    string idStr;
    vector<string> idList;
    if(match(tokens.at(n),ID)){
      idStr = tokens.at(n).getTokenStr();
      n++;
    }
    else{
      throw tokens.at(n);
    }
    if(match(tokens.at(n),LEFT_PAREN)){
      n++;
    }
    else{
      throw tokens.at(n);
    }
    if(match(tokens.at(n),ID)){
      idList.push_back(tokens.at(n).getTokenStr());
      n++;
    }
    else{
      throw tokens.at(n);
    }
    parseIDList(idList);
    if(match(tokens.at(n),RIGHT_PAREN)){
      n++;
    }
    else{
      throw tokens.at(n);
    }
    schemeVector.push_back(predicate(idStr,idList));
}
void parser::parseSchemeList(vector<predicate>& schemeVector)
{
    if(!match(tokens.at(n),FACTS)){
      parseScheme(schemeVector);
      parseSchemeList(schemeVector);
    }
}
void parser::parseFactList(vector<predicate>& factVector)
{
    if(!match(tokens.at(n),RULES)){
      parseFact(factVector);
      parseFactList(factVector);
    }
}
void parser::parseFact(vector<predicate>& factVector)
{
  string idStr;
  vector<string> stringList;
  if(match(tokens.at(n),ID)){
    idStr = tokens.at(n).getTokenStr();
    n++;
  }
  else{
    throw tokens.at(n);
  }
  if(match(tokens.at(n),LEFT_PAREN)){
    n++;
  }
  else{
    throw tokens.at(n);
  }
  if(match(tokens.at(n),STRING)){
    stringList.push_back(tokens.at(n).getTokenStr());
    n++;
  }
  else{
    throw tokens.at(n);
  }
  parseStringList(stringList);
  if(match(tokens.at(n),RIGHT_PAREN)){
    n++;
  }
  else{
    throw tokens.at(n);
  }
  if(match(tokens.at(n),PERIOD)){
    n++;
  }
  else{
    throw tokens.at(n);
  }
  factVector.push_back(predicate(idStr,stringList));
}
void parser::parseRuleList(vector<rule>& ruleVector)
{
    if(!match(tokens.at(n),QUERIES)){
      parseRule(ruleVector);
      parseRuleList(ruleVector);
    }
}
void parser::parseRule(vector<rule>& ruleVector)
{
    vector<predicate> predicateVector;
    predicateVector.push_back(parseHeadPredicate());
    if(match(tokens.at(n),COLON_DASH)){
      n++;
    }
    else{
      throw tokens.at(n);
    }
    parsePredicate(predicateVector);
    parsePredicateList(predicateVector);
    if(match(tokens.at(n),PERIOD)){
      n++;
    }
    else{
      throw tokens.at(n);
    }
    ruleVector.push_back(rule(predicateVector));
}
void parser::parseQuery(vector<predicate>& queryVector)
{
    parsePredicate(queryVector);
    if(match(tokens.at(n),Q_MARK)){
      n++;
    }
    else{
      throw tokens.at(n);
    }
}
void parser::parseQueryList(vector<predicate>& queryVector)
{
  if(!match(tokens.at(n),END)){
    parseQuery(queryVector);
    parseQueryList(queryVector);
  }
}
predicate parser::parseHeadPredicate()
{
  string idStr;
  vector<string> idList;
  if(match(tokens.at(n),ID)){
    idStr = tokens.at(n).getTokenStr();
    n++;
  }
  else{
    throw tokens.at(n);
  }
  if(match(tokens.at(n),LEFT_PAREN)){
    n++;
  }
  else{
    throw tokens.at(n);
  }
  if(match(tokens.at(n),ID)){
    idList.push_back(tokens.at(n).getTokenStr());
    n++;
  }
  else{
    throw tokens.at(n);
  }
  parseIDList(idList);
  if(match(tokens.at(n),RIGHT_PAREN)){
    n++;
  }
  else{
    throw tokens.at(n);
  }
  return predicate(idStr,idList);
}
void parser::parsePredicate(vector<predicate>& predicateVector)
{
  string idStr;
  vector<string> paramVector;
  vector<TokenType> tTypeVector;
  if(match(tokens.at(n),ID)){
    idStr = tokens.at(n).getTokenStr();
    n++;
  }
  else{
    throw tokens.at(n);
  }
  if(match(tokens.at(n),LEFT_PAREN)){
    n++;
  }
  else{
    throw tokens.at(n);
  }
  parseParameter(paramVector,tTypeVector);
  parseParameterList(paramVector,tTypeVector);
  if(match(tokens.at(n),RIGHT_PAREN)){
    n++;
  }
  else{
    throw tokens.at(n);
  }
  predicateVector.push_back(predicate(idStr,paramVector,tTypeVector));
}
void parser::parsePredicateList(vector<predicate>& predicateVector)
{
    if(!match(tokens.at(n),PERIOD)){
      if(match(tokens.at(n),COMMA)){
        n++;
      }
      else{
        throw tokens.at(n);
      }
      parsePredicate(predicateVector);
      parsePredicateList(predicateVector);
    }
}
void parser::parseParameterList(vector<string>& paramVector,vector<TokenType>& tTypeVector)
{
  if(!match(tokens.at(n),RIGHT_PAREN)){
    if(match(tokens.at(n),COMMA)){
      n++;
    }
    else{
      throw tokens.at(n);
    }
    parseParameter(paramVector,tTypeVector);
    parseParameterList(paramVector,tTypeVector);
  }
}
void parser::parseParameter(vector<string>& paramVector,vector<TokenType>& tTypeVector)
{
    if(match(tokens.at(n),STRING)){
      paramVector.push_back(tokens.at(n).getTokenStr());
      tTypeVector.push_back(STRING);
      n++;
    }
    else if(match(tokens.at(n),ID)){
      paramVector.push_back(tokens.at(n).getTokenStr());
      tTypeVector.push_back(ID);
      n++;
    }
    else if(!match(tokens.at(n),RIGHT_PAREN)){
      paramVector.push_back(parseExpression());
    }
}
void parser::parseStringList(vector<string>& stringList)
{
    if(!match(tokens.at(n),RIGHT_PAREN)){
      if(match(tokens.at(n),COMMA)){
        n++;
      }
      else{
        throw tokens.at(n);
      }
      if(match(tokens.at(n),STRING)){
        stringList.push_back(tokens.at(n).getTokenStr());
        n++;
      }
      else{
        throw tokens.at(n);
      }
      parseStringList(stringList);
    }
}
void parser::parseIDList(vector<string>& idList)
{
  if(!match(tokens.at(n),RIGHT_PAREN)){
    if(match(tokens.at(n),COMMA)){
      n++;
    }
    else{
      throw tokens.at(n);
    }
    if(match(tokens.at(n),ID)){
      idList.push_back(tokens.at(n).getTokenStr());
      n++;
    }
    else{
      throw tokens.at(n);
    }
    parseIDList(idList);
  }
}
string parser::parseExpression()
{
  vector<string> rhs; //right hand side of expression
  vector<string> lhs; //left hand side of expression
  vector<TokenType> tTypeVector;
  string expression;
  if(match(tokens.at(n),LEFT_PAREN)){
    expression += "(";
    n++;
  }
  else{
    throw tokens.at(n);
  }
  parseParameter(lhs,tTypeVector);
  //appends parameters to the left hand side of the expression
  for(auto s : lhs){
    expression += s;
  }
  parseOperator(expression); //appends operator to the expression
  parseParameter(rhs,tTypeVector);
  //appends parameters to the right hand side of the expression
  for(auto s : rhs){
    expression += s;
  }
  if(match(tokens.at(n),RIGHT_PAREN)){
    expression += ")";
    n++;
  }
  else{
    throw tokens.at(n);
  }
  return expression;
}
void parser::parseOperator(string& expression)
{
  if(match(tokens.at(n),ADD)){
    expression += "+";
    n++;
  }
  else if(match(tokens.at(n),MULTIPLY)){
    expression += "*";
    n++;
  }
  else{
    throw tokens.at(n);
  }
}
