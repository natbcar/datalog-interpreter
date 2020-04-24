#include "DatalogProgram.h"
#include <set>

DatalogProgram::DatalogProgram()
{

}
DatalogProgram::DatalogProgram(vector<rule>& rules, vector<predicate>& schemes, vector<predicate>& facts, vector<predicate>& queries)
{
    this->rules = rules;
    this->schemes = schemes;
    this->facts = facts;
    this->queries = queries;
    this->schemes = schemes;

    vector<string> tempDomain;
    for(unsigned int i = 0; i < facts.size(); i++){
      tempDomain.insert(tempDomain.begin(),facts.at(i).getDomain().begin(),facts.at(i).getDomain().end());
    }
    for(auto s : tempDomain){
      domain.insert(s);
    }
}
string DatalogProgram::toString()
{
    stringstream ss;
    ss << "Schemes(" << schemes.size() << "):" << endl;
    for(unsigned int i = 0; i < schemes.size(); i++){
      ss << "  " << schemes.at(i).toString() << endl;
    }
    ss << "Facts(" << facts.size() << "):" << endl;
    for(unsigned int i = 0; i < facts.size(); i++){
      ss << "  " << facts.at(i).toString() << "." << endl;
    }
    ss << "Rules(" << rules.size() << "):" << endl;
    for(unsigned int i = 0; i < rules.size(); i++){
      ss << "  " << rules.at(i).toString() << "." << endl;
    }
    ss << "Queries(" << queries.size() << "):" << endl;
    for(unsigned int i = 0; i < queries.size(); i++){
      ss << "  " << queries.at(i).toString() << "?" << endl;
    }
    ss << "Domain(" << domain.size() << "):" << endl;
    //creates iterator to iterate through the domain set
    std::set<std::string>::iterator it = domain.begin();
    while(it != domain.end()){
      ss << "  " << (*it) << endl;
      it++;
    }
    return ss.str();
}
