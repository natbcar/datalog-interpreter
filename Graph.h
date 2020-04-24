#pragma once

#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <stack>
#include <queue>
#include "Node.h"
#include "rule.h"
#include "predicate.h"

using namespace std;

class Graph{
private:
  map<int, Node> nodes;
  vector<rule> ruleVector;
  stack<int> postOrderTracker;
  stack<int> topologicalSort;
  set<int> visited;
  vector<set<int>> scc;
public:
  Graph(vector<rule>& ruleVector);
  void dfs(Node& tempNode);
  stack<int> dfsForest();
  vector<set<int>> buildSCC(stack<int>& postOrder);
  string printGraph();
  void addEdge(int startingNode, int endingNode);
  string sccToString(int i);
  bool isSelfDependent(int i);
};
