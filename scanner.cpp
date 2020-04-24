#include "scanner.h"

scanner::scanner(string fileName)
{
    this->fileName = fileName;
}
void scanner::tokenize()
{
    int lineNum = 1; //counts line number starting from 1
    string tokenStr; //stores token string to be added
    TokenType tType;
    char space = ' ';
    char tab = '\t';
    char newline = '\n';
    char c;
    char state;

    //creates ifstream object and open txt input file
    ifstream myFile(fileName.c_str());

    if(myFile){
        while(!myFile.eof()){

            c = myFile.get();

            if(c == newline){
                lineNum++; //updates line number
            }
            state = determineState(c, myFile);
            switch(state){
                case ',':
                {
                    tokenStr = ",";
                    tType = COMMA;
                    token newToken = token(tokenStr, lineNum, tType);
                    tokens.push_back(newToken);
                    break;
                }
                case '.':
                {
                    tokenStr = ".";
                    tType = PERIOD;
                    token newToken = token(tokenStr, lineNum, tType);
                    tokens.push_back(newToken);
                    break;
                }
                case '?':
                {
                    tokenStr = "?";
                    tType = Q_MARK;
                    token newToken = token(tokenStr, lineNum, tType);
                    tokens.push_back(newToken);
                    break;
                }
                case '(':
                {
                    tokenStr = "(";
                    tType = LEFT_PAREN;
                    token newToken = token(tokenStr, lineNum, tType);
                    tokens.push_back(newToken);
                    break;
                }
                case ')':
                {
                    tokenStr = ")";
                    tType = RIGHT_PAREN;
                    token newToken = token(tokenStr, lineNum, tType);
                    tokens.push_back(newToken);
                    break;
                }
                case ':':
                {
                    if(myFile.peek() == '-'){
                        c = myFile.get();
                        tokenStr = ":-";
                        tType = COLON_DASH;
                    }
                    else{
                        tokenStr = ":";
                        tType = COLON;
                    }
                    token newToken = token(tokenStr, lineNum, tType);
                    tokens.push_back(newToken);
                    break;
                }
                case '*':
                {
                    tokenStr = "*";
                    tType = MULTIPLY;
                    token newToken = token(tokenStr, lineNum, tType);
                    tokens.push_back(newToken);
                    break;
                }
                case '+':
                {
                    tokenStr = "+";
                    tType = ADD;
                    token newToken = token(tokenStr, lineNum, tType);
                    tokens.push_back(newToken);
                    break;
                }
                case '\'':
                {
                    string str;
                    str += state;
                    int tempLineNum = lineNum; //accounts for multi-line strings strings have to have line number on the line they originated on
                    char s;
                    bool runLoop = true;
                    bool unDef = false; //marked true on unterminated strings
                    while(runLoop){
                        s = myFile.get();
                        str += s;
                        if(s == '\''){
                            runLoop = determineString(myFile);
                            if(runLoop) {
                                s = myFile.get();
                                str += s;
                            }
                        }
                        if(s == newline){
                            lineNum++;
                        }
                        if(myFile.peek() == EOF){
                            runLoop = false;
                            unDef = true;
                        }
                    }
                    if(unDef){
                        tokenStr = str;
                        tType = UNDEFINED;
                        token newToken = token(tokenStr, tempLineNum, tType);
                        tokens.push_back(newToken);

                        //create eof token if the string does not terminate
                        s = myFile.get();
                        tType = END;
                        token eofToken = token("",lineNum,END);
                        tokens.push_back(eofToken);
                    }
                    else{
                        tokenStr = str;
                        tType = STRING;
                        token newToken = token(tokenStr, tempLineNum, tType);
                        tokens.push_back(newToken);
                    }
                    break;
                }
                case 'a':
                {
                    string str;
                    str += c;
                    while(isalpha(myFile.peek()) || isalnum(myFile.peek())){
                        str += myFile.get();
                    }
                    if(str == "Schemes"){
                        tType = SCHEMES;
                    }
                    else if(str == "Facts"){
                        tType = FACTS;
                    }
                    else if(str == "Rules"){
                        tType = RULES;
                    }
                    else if(str == "Queries"){
                        tType = QUERIES;
                    }
                    else{
                        tType = ID;
                    }
                    tokenStr = str;
                    token newToken = token(tokenStr, lineNum, tType);
                    tokens.push_back(newToken);
                    break;
                }
                case '#':
                {
                    string str;
                    str += state;
                    char s;
                    int tempLineNum = lineNum; //line num for multi line comments
                    bool unDef = false;
                    bool runLoop = true;
                    if(myFile.peek() == '|'){
                        do {
                            s = myFile.get();
                            str += s;
                            if(s == newline){
                                lineNum++;
                            }
                            if(s == '|'){
                                if(myFile.peek() == '#'){
                                    s = myFile.get();
                                    str += s;
                                    runLoop = false;
                                }
                            }
                        } while(runLoop && myFile.peek() != EOF);
                        if(myFile.peek() == EOF){
                            unDef = true;
                        }
                    }
                    else{
                        while(myFile.peek() != '\n' && myFile.peek() != EOF){
                            s = myFile.get();
                            str += s;
                        }
                    }
                    if(unDef){
                        tokenStr = str;
                        tType = UNDEFINED;
                        token newToken = token(tokenStr, tempLineNum, tType);
                        tokens.push_back(newToken);

                        //create eof token if comment is unterminated
                        s = myFile.get();
                        tType = END;
                        token eofToken = token("",lineNum,END);
                        tokens.push_back(eofToken);
                    }
                    else{
                        //tokenStr = str;
                        //tType = COMMENT;
                        //token newToken = token(tokenStr, tempLineNum, tType);
                        //tokens.push_back(newToken);
                    }
                    break;
                }
                case 'e':
                {
                    tokenStr = "";
                    tType = END;
                    token newToken = token(tokenStr, lineNum, tType);
                    tokens.push_back(newToken);
                    break;
                }
                default:
                {
                    if(state == tab || state == space || state == newline){
                        break;
                    }
                    else{
                        string str = "";
                        str += state;
                        tokenStr = str;
                        tType = UNDEFINED;
                        token newToken = token(tokenStr, lineNum, tType);
                        tokens.push_back(newToken);
                        break;
                    }
                    break;
                }
            }
        }
        // deletes all COMMENT tokens from token vector before parsing
        for(std::vector<token>::iterator it = tokens.begin(); it != tokens.end(); it++){
          if(it->getType() == COMMENT){
            tokens.erase(it);
          }
        }
    }

}
char scanner::determineState(char c, ifstream& myFile)
{
    if(isalpha(c)){
        return 'a';
    }
    else if(isalnum(c)){
        return c;
    }
    else if(myFile.peek() == EOF){
        return 'e';
    }
    return c;
}
bool scanner::determineString(ifstream& myFile)
{
    if(myFile.peek() == '\''){
        return true;
    }
    return false;
}
void scanner::printTokens()
{
    for(unsigned int i = 0; i < tokens.size(); i++){
        cout << tokens.at(i).toString() << endl;
    }
    cout << "Total Tokens = " << tokens.size() << endl;
}
vector<token>& scanner::getTokens()
{
  return tokens;
}
