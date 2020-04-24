#include "rule.h"

rule::rule(vector<predicate> predicateList)
{
  this->predicateList = predicateList;
}
string rule::toString()
{
  stringstream ss;

  for(unsigned int i = 0; i < predicateList.size(); i++){
    if(i == 0){
      ss << predicateList.at(i).toString() << " :- ";
    }
    else if(i == predicateList.size() - 1){
      ss << predicateList.at(i).toString();
    }
    else{
      ss << predicateList.at(i).toString() << ",";
    }

  }
  return ss.str();
}
vector<predicate> rule::getPredicateList()
{
    vector<predicate> tempPredList;
    for(unsigned int i = 1; i < predicateList.size(); i++){
      tempPredList.push_back(predicateList[i]);
    }
    return tempPredList;
}
predicate rule::getHeadPredicate()
{
    return predicateList[0];
}
