#include <iostream>
#include <string>
#include "DatalogProgram.h"
#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "relation.h"
#include "scheme.h"
#include "Tuple.h"

using namespace std;

int main(int argc, char *argv[]){

    string fileName  = argv[1];
    scanner newScanner = scanner(fileName);
    newScanner.tokenize();
    parser newParser = parser(newScanner.getTokens());
    newParser.parse();

    return 0;
}
