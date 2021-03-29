//
// Created by Paulo Sousa on 13/03/2021.
//

#ifndef GENERATOR_PARSER_H
#define GENERATOR_PARSER_H

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include "tinyxml2.h"
#include "../src/point.h"
#include "group.h"

using namespace tinyxml2;
using namespace std;

vector<Group *> parseXML(char * path);

#endif //GENERATOR_PARSER_H
