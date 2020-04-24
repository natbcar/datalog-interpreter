#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include "token.h"

using namespace std;

class scanner{
    private:
    string fileName;
    vector<token> tokens;

    public:
    scanner(string fileName);
    void tokenize();
    char determineState(char c, ifstream& myFile); //determines state
    bool determineString(ifstream& myFile); //determines if a string has terminated or not
    void printTokens();
    vector<token>& getTokens();
};
