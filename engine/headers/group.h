#ifndef GENERATOR_GROUP_H
#define GENERATOR_GROUP_H

#include <vector>
#include "shape.h"
#include "transformation.h"

using namespace std;

class Group {
private:
    vector<Transformation*> transf;
    vector<Shape*> models;
    vector<Group*> groups;

public:
    Group(vector<Transformation*> t, vector<Shape*> m, vector<Group*> g);

    void render();

    static void renderGroups(vector<Group *> groups);
};

#endif //GENERATOR_GROUP_H
