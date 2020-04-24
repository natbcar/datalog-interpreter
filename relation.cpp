#include "relation.h"

relation::relation(string name, scheme schemeVector)
{
  this->name = name;
  this->schemeVector = schemeVector;
}
relation::relation(string name, scheme schemeVector, set<Tuple> Tuples)
{
    this->name = name;
    this->schemeVector = schemeVector;
    this->Tuples = Tuples;
}
void relation::addTuple(Tuple newTuple)
{
    Tuples.insert(newTuple);
}
string relation::toString()
{
    stringstream ss;

    std::set<Tuple>::iterator it = Tuples.begin();
    while(it != Tuples.end()){
        for(unsigned int i = 0; i < schemeVector.size(); i++){
          vector<string> tmpVector = *it;
          if(i == 0){
            ss << "  ";
          }
          if(i == schemeVector.size() - 1){
            ss <<schemeVector[i] << "=" << tmpVector[i] << endl;
          }
          else{
            ss << schemeVector[i] << "=" << tmpVector[i] << ", ";
          }
        }
        it++;
    }
    return ss.str();
}
relation relation::select(int position, string value)
{
    set<Tuple> newTuples;
    for(Tuple t : Tuples){
      if(t[position] == value){
        newTuples.insert(t);
      }
    }
    return relation(name,schemeVector,newTuples);
}
relation relation::select(int position1, int position2)
{
    set<Tuple> newTuples;
    for(Tuple t: Tuples){
      if(t[position1] == t[position2]){
        newTuples.insert(t);
      }
    }
    return relation(name,schemeVector,newTuples);
}
relation relation::project(vector<int> positions)
{
    scheme newScheme;
    set<Tuple> newTuples;
    for(unsigned int i = 0; i < positions.size(); i++){
      newScheme.push_back(schemeVector[positions[i]]);
    }
    for(Tuple t : Tuples){
      Tuple tempTuple;
      for(unsigned int i = 0; i < positions.size(); i++){
        tempTuple.push_back(t[positions[i]]);
      }
      newTuples.insert(tempTuple);
    }
    return relation(name,newScheme,newTuples);
}
relation relation::rename(vector<string> strVector)
{
    scheme newScheme;
    for(unsigned int i = 0; i < strVector.size(); i++){
      newScheme.push_back(strVector[i]);
    }
    return relation(name,newScheme,Tuples);
}
relation relation::join(relation joinRelt)
{
    //tracks the colum indeces that must be equal in the two tuples
    //in order for the tuples to be combined

    vector<int> alpha;
    vector<int> beta;
    for(unsigned int i = 0; i < schemeVector.size(); i++){
      for(unsigned int j = 0; j < joinRelt.getSchemes().size(); j++){
        if(schemeVector.at(i) == joinRelt.getSchemes().at(j)){
          alpha.push_back(i);
          beta.push_back(j);
        }
      }
    }

    scheme newScheme = combineScheme(schemeVector,joinRelt.getSchemes());
    relation newRelation = relation(name,newScheme);

    for(Tuple t1 : Tuples){
      for(Tuple t2 : joinRelt.getTuples()){
        if(isJoinable(t1,t2,alpha,beta)){
          Tuple newTup = combineTuples(t1,t2,beta);
          newRelation.addTuple(newTup);
        }
      }
    }
    return newRelation;
}
relation relation::unify(relation unionRelt)
{
    if(schemeVector == unionRelt.getSchemes()){
      set<Tuple> newTuples;
      for(Tuple t : Tuples){
        newTuples.insert(t);
      }
      for(Tuple t : unionRelt.getTuples()){
        if(newTuples.insert(t).second){
          for(unsigned int i = 0; i < t.size(); i++){
            if(i == 0){
              cout << "  ";
            }
            if(i == t.size() - 1){
              cout <<schemeVector[i] << "=" << t[i] << endl;
            }
            else{
              cout << schemeVector[i] << "=" << t[i] << ", ";
            }
          }
        }
      }
      return relation(name,schemeVector,newTuples);
    }
    return relation(name,schemeVector,Tuples);
}
scheme relation::combineScheme(scheme s1, scheme s2)
{
    scheme newScheme;
    for(string s : s1){
      newScheme.push_back(s);
    }
    for(string s : s2){
      bool exists = false;
      for(string str : newScheme){
        if(str == s){
          exists = true;
        }
      }
      if(!exists){
        newScheme.push_back(s);
      }
    }
    return newScheme;
}
Tuple relation::combineTuples(Tuple t1, Tuple t2, vector<int> beta)
{
    Tuple newTuple;
    for(unsigned int i = 0; i < t1.size(); i++){
      newTuple.push_back(t1[i]);
    }

    int fake_i = 0;
    for(unsigned int i = 0; i < t2.size(); i++){
      bool addTup = true;
      for(unsigned int j = 0; j < beta.size(); j++){
        if(fake_i == beta[j]){
          addTup = false;
        }
      }
      if(addTup == true){
        newTuple.push_back(t2[i]);
      }
      fake_i++;
    }
    return newTuple;
}
set<Tuple> relation::getTuples()
{
    return Tuples;
}
scheme relation::getSchemes()
{
    return schemeVector;
}
bool relation::isJoinable(Tuple t1, Tuple t2, vector<int> alpha, vector<int> beta)
{
    for(unsigned int i = 0; i < alpha.size(); i++){
      if(t1[alpha[i]] != t2[beta[i]]){
        return false;
      }
    }
    return true;
}
bool relation::isEmpty()
{
    if(Tuples.size() == 0){
      return true;
    }
    return false;
}
int relation::numRows()
{
    return Tuples.size();
}
