#pragma once

#include <iostream>
#include <map>
#include "relation.h"

using namespace std;

class DataBase: public map<string, relation>{};
