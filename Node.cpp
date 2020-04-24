#include "Node.h"

Node::Node(int id)
{
  this->id = id;
  selfDependent = false;
}
void Node::addEdge(int& adjecentNode)
{
  adjList.insert(adjecentNode);
}
set<int> Node::getAdjList()
{
  return adjList;
}
int Node::getID()
{
  return id;
}
