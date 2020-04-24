#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include "rule.h"
#include "predicate.h"
#include "parameter.h"
using namespace std;

class DatalogProgram{
    private:
      //vectors to store rules,schemes,facts,and queries
      vector<rule> rules;
      vector<predicate> schemes;
      vector<predicate> facts;
      vector<predicate> queries;
      set<string> domain;
      friend class Interpreter;
    public:
      DatalogProgram();
      DatalogProgram(vector<rule>& rules, vector<predicate>& schemes, vector<predicate>& facts, vector<predicate>& queries);
      string toString(); //returns a string with all of the objects in the Datelog Program
};
