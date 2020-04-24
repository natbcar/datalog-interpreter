#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram dlProgram)
{
  this->dlProgram = dlProgram;
  //creating the relations from the schemes in the DLP and storing them in the database
  for(predicate s : dlProgram.schemes){
    scheme schemeVector = scheme();
    vector<string> tmpVector = s.getDomain();
    for(unsigned int i = 0; i < tmpVector.size(); i++){
      schemeVector.push_back(tmpVector[i]);
    }
    string name = s.getID();
    relation tempRelation = relation(s.getID(),schemeVector);
    if(dataBase.find(name) == dataBase.end()){
      dataBase.insert(std::pair<string,relation>(name,tempRelation));
    }
  }
  //populating the database with tuples using facts from dlProgram
  for(predicate fact : dlProgram.facts){
    Tuple tupleVector;
    vector<string> tmpVector = fact.getDomain();
    for(unsigned int i = 0; i < tmpVector.size(); i++){
      tupleVector.push_back(tmpVector[i]);
    }
    string key = fact.getID();
    dataBase.find(key)->second.addTuple(tupleVector);
  }
}
void Interpreter::processInput()
{
  //create graph and reverse graph with rules from datalog program
  Graph forwardGraph = Graph(dlProgram.rules);
  Graph reverseGraph = Graph(dlProgram.rules);


  //add edges on forward graph and reverse graph
  vector<rule> ruleVector = dlProgram.rules;
  for(unsigned int i = 0; i < ruleVector.size(); i++){
    vector<predicate> bodyPredicates = ruleVector.at(i).getPredicateList(); //getting body predicates for rule
    for(unsigned int j = 0; j < bodyPredicates.size(); j++){
      for(unsigned int k = 0; k < ruleVector.size(); k++){
        if(bodyPredicates.at(j).getID() == ruleVector.at(k).getHeadPredicate().getID()){
          forwardGraph.addEdge(i,k);
          reverseGraph.addEdge(k,i);
        }
      }
    }
  }
  cout << "Dependency Graph" << endl;
  cout << forwardGraph.printGraph() << endl; //printing dependency graph
  
  //run DFS Forest algorithm on reverse dependency graph
  //in order to find post order number for each Node
  stack<int> postOrder = reverseGraph.dfsForest();

  //get strongly connected components by running
  //dfs on forward graph starting with highest post order number
  vector<set<int>> scc = forwardGraph.buildSCC(postOrder);

  //run fixed point algorithm on individual strongly connected components
  cout << "Rule Evaluation" << endl;
  for(unsigned int i = 0; i < scc.size(); i++){
    cout << "SCC: " << forwardGraph.sccToString(i);

    bool run = true;
    int numIters = 0;
    while(run){
      int beforeCount = 0;
      int afterCount = 0;

      //get before count of tuples
      for(pair<string, relation> s : dataBase){
        beforeCount += s.second.getTuples().size();
      }

      evalRule(scc[i]);

      //get after count of tuples
      for(pair<string, relation> s : dataBase){
        afterCount += s.second.getTuples().size();
      }

      if(beforeCount == afterCount){
        run = false;
      }
      if(scc[i].size() == 1){
        //accounting for trivial rules
        //if is not self dependent then set run to false
        auto first = scc[i].begin();
        if(!forwardGraph.isSelfDependent(*first)){
          run = false;
        }
      }

      //update num iterations
      numIters++;
    }
    cout << numIters << " passes: " << forwardGraph.sccToString(i);
  }
  cout << endl;
  cout << "Query Evaluation" << endl;
  evalQuerie();
}
void Interpreter::evalQuerie()
{
  for(predicate querie : dlProgram.queries){
    evalPredicate(querie);
  }
}
relation Interpreter::evalPredicate(predicate currPred, bool print)
{
      stringstream ss;
      for(pair<string, relation> s : dataBase){
        if(s.first == currPred.getID()){

          relation tempRelation = s.second;
          vector<TokenType> tTypeVector = currPred.getType();
          vector<string> querieVector = currPred.getDomain();
          vector<string> columns;
          vector<int> positions;
          map<string,int> variableTracker;

          for(unsigned int i = 0; i < tTypeVector.size(); i++){
            if(tTypeVector[i] == STRING){
              //select type one
              tempRelation = tempRelation.select(i,querieVector[i]);
            }
            else if(tTypeVector[i] == ID){
              //have we seen this variable before
              //if yes do a select type 2
              int columnIndex = i;
              std::map<string,int>::iterator it = variableTracker.find(querieVector[i]);
              if(it != variableTracker.end()){
                int position = it->second;
                tempRelation = tempRelation.select(i,position);
              }
              //if no mark for the project and rename
              else{
                variableTracker.insert(std::make_pair(querieVector[i],columnIndex));
                columns.push_back(querieVector[i]);
                positions.push_back(columnIndex);
              }
            }

          }
          tempRelation = tempRelation.project(positions);
          tempRelation = tempRelation.rename(columns);
          if(print == true){
            cout << currPred.toString() << "? ";
            if(!tempRelation.isEmpty()){
              cout << "Yes(" << tempRelation.numRows() << ")" << endl;
              cout << tempRelation.toString();
            }
            else{
              cout << "No" << endl;
            }
          }
          return tempRelation;
        }
      }
  //never returns below scheme, just added to prevent compile error
  scheme garbageScheme;
  return relation(" ",garbageScheme);
}
void Interpreter::evalRule(set<int> indices)
{
  //Evaluates the predicates on the rhs of each rule
  //joins resulting relations that are returned from predicate evaluation

  vector<rule> ruleVector;
  for(int i : indices){
    ruleVector.push_back(dlProgram.rules.at(i));
  }
  for(rule r : ruleVector){
    cout << r.toString() << "." << endl;
    predicate headPred = r.getHeadPredicate();
    vector<int> positions;
    vector<predicate> predicateList = r.getPredicateList();

    relation tempRelation = evalPredicate(predicateList.at(0),false);

    for(unsigned int i = 1; i < predicateList.size(); i++){
      tempRelation = tempRelation.join(evalPredicate(predicateList[i],false));
    }

    for(string s : headPred.getDomain()){
      for(unsigned int i = 0; i < tempRelation.getSchemes().size(); i++){
        if(s == tempRelation.getSchemes().at(i)){
          positions.push_back(i);
        }
      }
    }

    tempRelation = tempRelation.project(positions);

    for(pair<string, relation> s : dataBase){
      if(s.first == headPred.getID()){
        vector<string> tempStrVector;
        scheme tempScheme = s.second.getSchemes();
        for(unsigned int i = 0; i < tempScheme.size(); i++){
          tempStrVector.push_back(tempScheme[i]);
        }

        tempRelation = tempRelation.rename(tempStrVector);
        dataBase.find(s.first)->second = s.second.unify(tempRelation);
      }
    }
  }
}
