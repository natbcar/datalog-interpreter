#include "Graph.h"

Graph::Graph(vector<rule>& ruleVector)
{
  this->ruleVector = ruleVector;
  for(unsigned int i = 0; i < ruleVector.size(); i++){
    Node tempNode = Node(i);
    nodes.insert(std::pair<int,Node>(i,tempNode));
  }
}
void Graph::dfs(Node& tempNode)
{
  if(visited.find(tempNode.id) == visited.end()){
    visited.insert(tempNode.id);
    set<int> tempAdjList = tempNode.adjList;
    set<int>::iterator it;
    for(it = tempAdjList.begin(); it != tempAdjList.end(); it++){
      if(visited.find(nodes.find(*it)->second.id) == visited.end()){
        dfs(nodes.find(*it)->second);
      }
    }
    topologicalSort.push(tempNode.id);
  }
}

stack<int> Graph::dfsForest()
{
  for(pair<int, Node> tempNode : nodes){
    if(visited.find(tempNode.second.id) == visited.end()){
      dfs(tempNode.second);
    }
  }
  return topologicalSort;
}
vector<set<int>> Graph::buildSCC(stack<int>& postOrder)
{
  while(!postOrder.empty()){
    if(visited.find(postOrder.top()) == visited.end()){
      dfs(nodes.find(postOrder.top())->second);
    }

    set<int> newSCC;

    while(visited.find(postOrder.top()) != visited.end()){
      newSCC.insert(postOrder.top());
      postOrder.pop();
      if(postOrder.empty()){
        break;
      }
    }
    scc.push_back(newSCC);
  }
  return scc;
}
string Graph::printGraph()
{
  stringstream ss;
  map<int, Node>::iterator it;
  for(pair<int, Node> n : nodes){
    ss << "R" << n.first << ":";
    set<int> adjList = n.second.getAdjList();
    unsigned int k = 0; //keeps track of position in adjacency list
    for(int j : adjList){
      if(k == adjList.size() - 1){
        ss << "R" << j;
      }
      else{
        ss << "R" << j << ",";
      }
      k++;
    }
    ss << endl;
  }

  return ss.str();
}
void Graph::addEdge(int startingNode, int endingNode)
{
  if(startingNode == endingNode){
    nodes.find(startingNode)->second.selfDependent = true;
  }
  nodes.find(startingNode)->second.addEdge(endingNode);
}
string Graph::sccToString(int i)
{
  stringstream ss;

  unsigned int k = 0;
  for(int j : scc.at(i)){
    if(k == scc[i].size() - 1){
      ss << "R" << j;
    }
    else{
      ss << "R" << j << ",";
    }
    k++;
  }
  ss << endl;
  return ss.str();
}
bool Graph::isSelfDependent(int i)
{
  return nodes.find(i)->second.selfDependent;
}
