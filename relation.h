#pragma once

#include <iostream>
#include <set>
#include <sstream>
#include <algorithm>  
#include "Tuple.h"
#include "scheme.h"


using namespace std;

class relation {
    private:
      string name;
      scheme schemeVector;
      set<Tuple> Tuples;
    public:
      relation(string name, scheme schemeVector);
      relation(string name, scheme schemeVector, set<Tuple> Tuples);
      void addTuple(Tuple newTuple);
      string toString();
      relation select(int position, string value);
      relation select(int position1, int position2);
      relation project(vector<int> positions);
      relation rename(vector<string> strVector);
      relation join(relation joinRelt);
      relation unify(relation unionRelt);
      scheme combineScheme(scheme s1, scheme s2);
      Tuple combineTuples(Tuple t1, Tuple t2, vector<int> beta);
      set<Tuple> getTuples();
      scheme getSchemes();
      bool isJoinable(Tuple t1, Tuple t2, vector<int> alpha, vector<int> beta);
      bool isEmpty();
      int numRows();
};
