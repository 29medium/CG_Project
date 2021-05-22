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
#include "point.h"
#include "group.h"
#include "light.h"
#include "material.h"

using namespace tinyxml2;
using namespace std;

class Parser
{
private:
    vector<Group *> groups;
    Light *light;

public:
    Parser();
    vector<Group *> getGroups();
    Light *getLight();
    void parseXML(char *path);
    void clearGroupsAndLight();
};

#endif //GENERATOR_PARSER_H
