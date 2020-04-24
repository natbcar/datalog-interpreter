#pragma once

#include <iostream>
#include <set>

using namespace std;
class Node{
private:
  set<int> adjList;
  int id;
  bool selfDependent;
  friend class Graph;
public:
  Node(int id);
  void addEdge(int& adjecentNode);
  set<int> getAdjList();
  int getID();
};
