#ifndef GENERATOR_GROUP_H
#define GENERATOR_GROUP_H

#include <vector>
#include "../src/shape.h"
#include "transformation.h"

using namespace std;

class Group {
private:
    vector<Transformation*> transf;
    vector<Shape*> models;
    vector<Group*> groups;

public:
    Group();
    Group(vector<Transformation*> t, vector<Shape*> m, vector<Group*> g);
    vector<Transformation*> getTransformations();
    vector<Shape*> getModels();
    vector<Group*> getGroups();
    void setTransf(vector<Transformation *> transf);
    void setModels(vector<Shape *> models);
    void setGroups(vector<Group *> groups);
};

#endif //GENERATOR_GROUP_H
