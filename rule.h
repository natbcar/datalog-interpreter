#pragma once

#include <iostream>
#include <vector>
#include "predicate.h"

using namespace std;

class rule{
    private:
      vector<predicate> predicateList;
    public:
      rule(vector<predicate> predicateList);
      string toString();
      vector<predicate> getPredicateList();
      predicate getHeadPredicate();
};
