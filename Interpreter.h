#pragma once

#include "relation.h"
#include "DataBase.h"
#include "DatalogProgram.h"
#include "Graph.h"
#include "Node.h"
#include <sstream>
#include <map>

using namespace std;

class Interpreter{
    private:
      DatalogProgram dlProgram;
      DataBase dataBase;
    public:
      Interpreter(DatalogProgram dlProgram);
      relation evalPredicate(predicate currPred, bool print = true);
      void processInput();
      void evalQuerie();
      void evalRule(set<int> indices);
};
